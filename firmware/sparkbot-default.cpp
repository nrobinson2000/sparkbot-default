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

  redValue = 0;
  greenValue = 0;
  blueValue = 0;

  choice = 0; // Used for switching lights

  slaveMode = false;
}

void sparkbot::begin()
{
  neckservo.attach(NECKSERVO);
  leftservo.attach(LEFTSERVO);
  rightservo.attach(RIGHTSERVO); //Here we attach the three servos

  pinMode(RIGHTBUTTON, INPUT);  //We Enable the inputs.
  pinMode(LEFTBUTTON, INPUT);
  pinMode(PHOTORESISTOR, INPUT);
  pinMode(MICROPHONE, INPUT);

  pinMode(REDLED, OUTPUT); //LEDs
  pinMode(BLUELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

/*
  neckservo.write(90); // Reset servos and read the values.
  neckAngle = neckservo.read();
  rightservo.write(90);
  rightArmAngle = rightservo.read();
  leftservo.write(90);
  leftArmAngle = leftservo.read();
  */

  Particle.variable("neck", &neckAngle, INT);
  Particle.variable("rightArm", &rightArmAngle, INT);
  Particle.variable("leftArm", &leftArmAngle, INT);
  Particle.variable("brightness", &brightness, INT);

  auto moveHandler = std::bind(&sparkbot::moveCloud, this, std::placeholders::_1);
  Particle.function("moveServos", moveHandler);

  auto moodHandler = std::bind(&sparkbot::moodlightsCloud, this, std::placeholders::_1);
  Particle.function("moodlights", moodHandler);

  auto slaveHandler = std::bind(&sparkbot::slaveToggle, this, std::placeholders::_1);
  Particle.function("enableSlave", slaveHandler);
  Serial.begin(9600);
}

void sparkbot::switchLights()
{
  if (choice == 0)
  {
    red();
    choice = 1;
    return;
  }

  if (choice == 1)
  {
    blue();
    choice = 2;
    return;
  }

  if (choice == 2)
  {
    green();
    choice = 0;
    return;
  }
}

void sparkbot::red() //This function turns on the red, and turns off the blue and green
{
  analogWrite(REDLED, 255);
  redValue = 255;
  analogWrite(BLUELED, 0);
  blueValue = 0;
  analogWrite(GREENLED, 0);
  greenValue = 0;
}

void sparkbot::blue() //This function turns on the blue, and turns off the red and green
{
  analogWrite(REDLED, 0);
  redValue = 0;
  analogWrite(BLUELED, 255);
  blueValue = 0;
  analogWrite(GREENLED, 0);
  greenValue = 0;
}

void sparkbot::green() //This function turns on the green, and turns off the red and blue
{
  analogWrite(REDLED, 0);
  redValue = 0;
  analogWrite(BLUELED, 0);
  blueValue = 0;
  analogWrite(GREENLED, 255);
  greenValue = 255;
}

int sparkbot::moodlightsCloud(String data)
{
  String red = data.substring(0, 3);
  String green = data.substring(4, 7);
  String blue = data.substring(8,11);

  analogWrite(REDLED, red.toInt());
  redValue = red.toInt();
  analogWrite(GREENLED, green.toInt());
  greenValue = green.toInt();
  analogWrite(BLUELED, blue.toInt());
  blueValue = blue.toInt();

  Serial.println("Original String:" + data);
  Serial.println("RED:" + String(red.toInt()));
  Serial.println("GREEN:" + String(green.toInt()));
  Serial.println("BLUE:" + String(blue.toInt()));
  return 1;
}

void sparkbot::moodlights(int red, int green, int blue)
{
  analogWrite(REDLED, red);
  redValue = red;
  analogWrite(GREENLED, green);
  greenValue = green;
  analogWrite(BLUELED, blue);
  blueValue = blue;
}


void sparkbot::syncLights()
{
  const char *color = "";
  if (redValue == 255)
  {
    color = "red";
  }

  if (blueValue == 255)
  {
    color = "blue";
  }

  if (greenValue == 255)
  {
    color = "green";
  }

  Particle.publish("RGB", color);
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

  Particle.publish("syncServos", message);
}

void sparkbot::sync()
{
  syncLights();
  syncServos();
}

void sparkbot::moveNeck(int value)
{
  neckservo.write(value);
  delay(15);
}

void sparkbot::moveRight(int value)
{
  rightservo.write(value);
  delay(15);
}

void sparkbot::moveLeft(int value)
{
  leftservo.write(value);
  delay(15);
}

void sparkbot::playBuzzer(int value)
{
  analogWrite(BUZZER, value);
}

void sparkbot::stopBuzzer()
{
  analogWrite(BUZZER, 0);
}

int sparkbot::moveCloud(String data)
{
  String neckvalue = data.substring(0, 3);
  String rightvalue = data.substring(4, 7);
  String leftvalue = data.substring(8,11);

  if (neckvalue.toInt() != 200)
  {
    moveNeck(neckvalue.toInt());
  }
  if (rightvalue.toInt() != 200)
  {
    moveRight(rightvalue.toInt());
  }
  if (leftvalue.toInt() != 200)
  {
    moveLeft(leftvalue.toInt());
  }

  Serial.println("Original String: " + data);
  Serial.println("Neck: " + String(neckvalue.toInt()));
  Serial.println("Right: " + String(rightvalue.toInt()));
  Serial.println("Left: " + String(leftvalue.toInt()));
  return 1;
}


int sparkbot::slaveToggle(String data)
{
  if (slaveMode == true)
  {
    slaveMode = false;
    return 1;
  }

  if (slaveMode == false)
  {
    slaveMode = true;
    return 2;
  }
  return -1;

}

void sparkbot::syncServosSlave(const char *event, const char *data)
{
  if (slaveMode == false) {return;}

  String message = String(data);

  String neckresult = message.substring(0, 3);
  String rightresult = message.substring(3, 6);
  String leftresult = message.substring(6,9);

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
  if (slaveMode == false) {return;}

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

void sparkbot::startLeftButton()
{
  auto leftInterruptHandler = std::bind(&sparkbot::switchLights, this);
  attachInterrupt(LEFTBUTTON, leftInterruptHandler, RISING);
}

void sparkbot::startRightButton()
{
  auto rightInterruptHandler = std::bind(&sparkbot::sync, this);
  attachInterrupt(RIGHTBUTTON, rightInterruptHandler, RISING);
}

float sparkbot::getTempC(int pin)
{
  float tempC;
  tempC = analogRead(pin);
  tempC = tempC * 0.48828125;
  return tempC;
}

int sparkbot::lightness()
{
  return analogRead(PHOTORESISTOR);
}

void sparkbot::refresh()
{
  brightness = lightness();
  /*
  neckAngle = neckservo.read();
  rightArmAngle = rightservo.read();
  leftArmAngle = leftservo.read();
  */

}
