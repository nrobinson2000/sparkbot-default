#include "sparkbot-default.h"
#include "application.h"

Servo rightservo;
Servo leftservo;
Servo neckservo;

sparkbot::sparkbot()
{
  // 3 Servo angles
  neckAngle = 0;
  rightArmAngle = 0;
  leftArmAngle = 0;

  // 2 Buttons
  rightbutton = D7;
  leftbutton = D3;

  // 3 LED Pins
  redled = D0;
  blueled = D1;
  greenled = D2;

  // 3 LED Booleans
  redledOn = false;
  blueledOn = false;
  greenledOn = false;

  // 2 Analog Sensor Pins
  photoresistor = A5;
  microphone = A3;

  // 1 Other Pins
  buzzer = A4;

  // 4 I/O pins
  /*io1 = A9;
  io2 = A8;
  */
  io3 = A7;
  io4 = A2;
  io5 = A1;
  io6 = A0;

  // 3 Servo pins
  rightServoPin = D4;
  leftServoPin = D5;
  neckServoPin = D6;

  choice = 0; // Used for switching lights
}

void sparkbot::startup()
{
  rightservo.attach(rightServoPin); //Here we attach the three servos
  leftservo.attach(leftServoPin);
  neckservo.attach(neckServoPin);

  pinMode(rightbutton, INPUT);  //We define the two button pins as inputs.
  pinMode(leftbutton, INPUT);

  pinMode(redled, OUTPUT); //LEDs
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

  Spark.variable("neck", &neckAngle, INT);
  Spark.variable("rightArm", &rightArmAngle, INT);
  Spark.variable("leftArm", &leftArmAngle, INT);

  Spark.function("moveNeck", (int (*)(String))&sparkbot::moveNeckCloud);
  Spark.function("moveRight", (int (*)(String))&sparkbot::moveRightCloud);
  Spark.function("moveLeft", (int (*)(String))&sparkbot::moveLeftCloud);
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
    color = "blue";
  }

  if (greenledOn == true)
  {
    color = "green";
  }

  Spark.publish("RGB", color);
}

void sparkbot::syncServos()
{
  String message = String("");
  String neckdata = String("");
  String rightdata = String("");
  String leftdata = String("");

  int neck = neckservo.read();
  int right = rightservo.read();
  int left = leftservo.read();

  bool neckchanged = false;
  bool rightchanged = false;
  bool leftchanged = false;

  if (neckAngle != neck)
  {
    neckAngle = neck;
    neckchanged = true;
    if (neck < 100 && neck > 9)
    {
      neckdata = String("0" + String(neck));
    }
    if (neck < 10)
    {
      neckdata = String("00" +String(neck));
    }
    else
    {
      neckdata = String(neck);
    }
  }

  if (rightArmAngle != right)
  {
    rightArmAngle = right;
    rightchanged = true;

    if (right < 100 && right > 9)
    {
      rightdata = String("0" + String(right));
    }
    if (right < 10)
    {
      rightdata = String("00" +String(right));
    }
    else
    {
      rightdata = String(right);
    }
  }

  if (leftArmAngle != left)
  {
    leftArmAngle = left;
    leftchanged = true;

    if (left < 100 && left > 9)
    {
      leftdata = String("0" + String(left));
    }
    if (left < 10)
    {
      leftdata = String("00" +String(left));
    }
    else
    {
      leftdata = String(left);
    }
  }

switch (neckchanged)
{
  case true:
  message += neckdata;
  break;

  case false:
  message += String("200");
}

switch (rightchanged)
{
  case true:
  message += rightdata;
  break;

  case false:
  message += String("200");
  break;
}

switch (leftchanged)
{
  case true:
  message += leftdata;
  break;

  case false:
  message += String("200");
}

Spark.publish("syncServos", message);


}

void sparkbot::moveNeck(int value)
{
  neckservo.write(value);
  neckAngle = neckservo.read();
}

void sparkbot::moveRight(int value)
{
  rightservo.write(value);
  rightArmAngle = rightservo.read();
}

void sparkbot::moveLeft(int value)
{
  leftservo.write(value);
  leftArmAngle = leftservo.read();
}

void sparkbot::playBuzzer(int value)
{
  analogWrite(buzzer, value);
}

void sparkbot::stopBuzzer()
{
  analogWrite(buzzer, 0);
}

int sparkbot::moveNeckCloud(const char *data)
{
  sparkbot::moveNeck(atoi(data));
  return 1;
}

int sparkbot::moveRightCloud(const char *data)
{
  sparkbot::moveRight(atoi(data));
  return 1;
}

int sparkbot::moveLeftCloud(const char *data)
{
  sparkbot::moveLeft(atoi(data));
  return 1;
}



void sparkbot::syncServosSlave(const char *event, const char *data)
{
  String message = String(data);
  String neckresult = String(message.charAt(0) + message.charAt(1) + message.charAt(2));
  String rightresult = String(message.charAt(3) + message.charAt(4) + message.charAt(5));
  String leftresult = String(message.charAt(6) + message.charAt(7) + message.charAt(8));

  bool moveNeck = false;
  bool moveRight = false;
  bool moveLeft = false;

  if (neckresult.toInt() >= 0 && neckresult.toInt() <= 180)
  {
    moveNeck = true;
  }

  if (rightresult.toInt() >= 0 && rightresult.toInt() <= 180)
  {
    moveRight = true;
  }

  if (leftresult.toInt() >= 0 && leftresult.toInt() <= 180)
  {
    moveLeft = true;
  }


  if (moveNeck == true)
  {
    sparkbot::moveNeck(neckresult.toInt());
  }

  if (moveRight == true)
  {
    sparkbot::moveRight(rightresult.toInt());
  }

  if (moveLeft == true)
  {
    sparkbot::moveLeft(leftresult.toInt());
  }
}

void sparkbot::RGBSlave(const char *event, const char *data)
{
  if (strcmp(data, "red") == 0)
  {
    red();
  }

  if (strcmp(data, "blue") == 0)
  {
    blue();
  }

  if (strcmp(data, "green") == 0)
  {
    green();
  }
}

float sparkbot::getTempC(int pin)
{
  float tempC;
  tempC = analogRead(pin);
  tempC = tempC * 0.48828125;
  return tempC;
}

void sparkbot::initiateSlave()
{
Spark.subscribe("syncServos", (EventHandler)&sparkbot::syncServosSlave, MY_DEVICES);
Spark.subscribe("RGB", (EventHandler)&sparkbot::RGBSlave, MY_DEVICES);

}

void sparkbot::sync()
{
syncLights();
syncServos();
}

void sparkbot::startLeftButton()
{
attachInterrupt(leftbutton, (voidFuncPtr)&sparkbot::switchLights, RISING);
}

void sparkbot::startRightButton()
{
attachInterrupt(rightbutton, (voidFuncPtr)&sparkbot::sync, RISING);
}

int sparkbot::sparkbotsOnline()
{
  Spark.publish("online?");
  return 1;
}

int sparkbot::moodlights(int red, int blue, int green)
{
  analogWrite(redled, red);
  analogWrite(blueled, blue);
  analogWrite(greenled, green);
  return 1;
}
