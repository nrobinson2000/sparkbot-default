#include "sparkbot-default.h"
#include "application.h"

Servo rightservo;
Servo leftservo;
Servo neckservo;

sparkbot::sparkbot()
{
  // Servo angles
  neckAngle = 0;
  rightArmAngle = 0;
  leftArmAngle = 0;

  // Buttons
  rightbutton = D7;
  leftbutton = D3;

  // LED Pins
  redled = D4;
  blueled = D5;
  greenled = D6;

  // LED Booleans
  redledOn = false;
  blueledOn = false;
  greenledOn = false;

  // Analog Sensor Pins
  temperature = A5;
  microphone = A1;

  // Other Pins
  buzzer = A0;

  // I/O pins
  io1 = A2;
  io2 = A3;
  io3 = A4;

  choice = 0; // Used for random tests


}


void sparkbot::startup()
{
  rightservo.attach(D0); //Here we attach the three servos
  leftservo.attach(D1);
  neckservo.attach(D2);

  pinMode(rightbutton, INPUT);  //We define the two button pins as inputs.
  pinMode(leftbutton, INPUT);

  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(greenled, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(microphone, INPUT);

  neckservo.write(90); // Reset servos and read the values.
  neckAngle = neckservo.read();
  rightservo.write(90);
  rightArmAngle = rightservo.read();
  leftservo.write(90);
  leftArmAngle = leftservo.read();
}


void sparkbot::switchLights()
{
  if (choice == 0)
  {
    digitalWrite(redled, HIGH);
    redledOn = true;
    digitalWrite(blueled, LOW);
    blueledOn = false;
    digitalWrite(greenled, LOW);
    greenledOn = false;
    choice = 1;
    return;
  }

  if (choice == 1)
  {
    digitalWrite(redled, LOW);
    redledOn = false;
    digitalWrite(blueled, HIGH);
    blueledOn = true;
    digitalWrite(greenled, LOW);
    greenledOn = false;
    choice = 2;
    return;
  }

  if (choice == 2)
  {
    digitalWrite(redled, LOW);
    redledOn = false;
    digitalWrite(blueled, LOW);
    blueledOn = false;
    digitalWrite(greenled, HIGH);
    greenledOn = true;
    choice = 0;
    return;
  }
}

void sparkbot::red() //This function turns on the red, and turns off the blue and green
{
  digitalWrite(redled, HIGH);
  redledOn = true;
  digitalWrite(blueled, LOW);
  blueledOn = false;
  digitalWrite(greenled, LOW);
  greenledOn = false;
}

void sparkbot::blue() //This function turns on the blue, and turns off the red and green
{
  digitalWrite(redled, LOW);
  redledOn = false;
  digitalWrite(blueled, HIGH);
  blueledOn = true;
  digitalWrite(greenled, LOW);
  greenledOn = false;
}

void sparkbot::green() //This function turns on the green, and turns off the red and blue
{
  digitalWrite(redled, LOW);
  redledOn = false;
  digitalWrite(blueled, LOW);
  blueledOn = false;
  digitalWrite(greenled, HIGH);
  greenledOn = true;
  choice = 0;
}

void sparkbot::syncLights()
{
  const char *color = "";
  if (redledOn == true)
  {
    color = "red";
  }

  if (blueledOn == true)
  {
    color = "blue"
  }

  if (greenledOn == true)
  {
    color = "green";
  }

  Spark.publish("RGB", color);
}

void sparkbot::syncServos()
{
  if (neckAngle != neckservo.read())
  {
    Spark.publish("moveNeck", String(neckservo.read()));
  }

  if (rightArmAngle != rightservo.read())
  {
    Spark.publish("moveRight", String(rightservo.read()));
  }

  if (leftArmAngle != leftservo.read())
  {
    Spark.publish("moveLeft", String(leftservo.read()));
  }
}

void sparkbot::moveNeck(int value)
{
  neckservo.write(value);
}

void sparkbot::moveRight(int value)
{
  rightservo.write(value);
}

void sparkbot::moveLeft(int value)
{
  leftservo.write(value);
}

void sparkbot::playBuzzer(int value)
{
  analogWrite(buzzer, value);
}

void sparkbot::stopBuzzer()
{
  analogWrite(buzzer, 0);
}


void sparkbot::moveNeckSlave(const char *event, const char *data)
{
  neckservo.write(atoi(data));
  return;
}

void sparkbot::moveRightSlave(const char *event, const char *data)
{
  rightservo.write(atoi(data));
  return;
}

void sparkbot::moveLeftSlave(const char *event, const char *data)
{
  leftservo.write(atoi(data));
  return;
}

void sparkbot::RGBSlave(const char *event, const char *data)
{
  if (data == "red")
  {
    red();
  }

  if (data == "blue")
  {
    blue();
  }

  if (data == "green")
  {
    green();
  }
}

float sparkbot::getTempC()
{
  float tempC;
  tempC = analogRead(temperature);
  tempC = tempC * 0.48828125;
  return tempC;
}

void sparkbot::initiateSlave()
{
Spark.subscribe("moveNeck", moveNeckSlave, MY_DEVICES);
Spark.subscribe("moveRight", moveRightSlave, MY_DEVICES);
Spark.subscribe("moveLeft", moveLeftSlave, MY_DEVICES);
Spark.subscribe("RGB", RGBSlave), MY_DEVICES);

}
