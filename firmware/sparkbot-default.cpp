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

  // 3 LED Booleans
  redledOn = false;
  blueledOn = false;
  greenledOn = false;

  choice = 0; // Used for switching lights

  onlineBots = 1;
}

void sparkbot::begin()
{
  rightservo.attach(RIGHTSERVO); //Here we attach the three servos
  leftservo.attach(LEFTSERVO);
  neckservo.attach(NECKSERVO);

  pinMode(RIGHTBUTTON, INPUT);  //We Enable the inputs.
  pinMode(LEFTBUTTON, INPUT);
  pinMode(PHOTORESISTOR, INPUT);

  pinMode(REDLED, OUTPUT); //LEDs
  pinMode(BLUELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(MICROPHONE, INPUT);

  neckservo.write(90); // Reset servos and read the values.
  neckAngle = neckservo.read();
  rightservo.write(90);
  rightArmAngle = rightservo.read();
  leftservo.write(90);
  leftArmAngle = leftservo.read();

  Spark.variable("neck", &neckAngle, INT);
  Spark.variable("rightArm", &rightArmAngle, INT);
  Spark.variable("leftArm", &leftArmAngle, INT);
  Spark.variable("brightness", &brightness, INT);

  Spark.variable("onlineBots", &onlineBots, INT);

  Spark.function("moveNeck", (int (*)(String))&sparkbot::moveNeckCloud);
  Spark.function("moveRight", (int (*)(String))&sparkbot::moveRightCloud);
  Spark.function("moveLeft", (int (*)(String))&sparkbot::moveLeftCloud);
  Spark.function("moodlights", (int (*)(String))&sparkbot::moodlights);
  Spark.function("checkOnline", (int (*)(String))&sparkbot::checkOnline);


  Spark.subscribe("online?", (EventHandler)&sparkbot::yesOnline, MY_DEVICES);
  Spark.subscribe("yesOnline", (EventHandler)&sparkbot::updateOnline, MY_DEVICES);
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
  digitalWrite(REDLED, HIGH);
  redledOn = true;
  digitalWrite(BLUELED, LOW);
  blueledOn = false;
  digitalWrite(GREENLED, LOW);
  greenledOn = false;
}

void sparkbot::blue() //This function turns on the blue, and turns off the red and green
{
  digitalWrite(REDLED, LOW);
  redledOn = false;
  digitalWrite(BLUELED, HIGH);
  blueledOn = true;
  digitalWrite(GREENLED, LOW);
  greenledOn = false;
}

void sparkbot::green() //This function turns on the green, and turns off the red and blue
{
  digitalWrite(REDLED, LOW);
  redledOn = false;
  digitalWrite(BLUELED, LOW);
  blueledOn = false;
  digitalWrite(GREENLED, HIGH);
  greenledOn = true;
}

int sparkbot::moodlights(const char *red, const char *green, const char *blue)
{
  analogWrite(REDLED, atoi(red));
  analogWrite(GREENLED, atoi(green));
  analogWrite(BLUELED, atoi(blue));
  return 1;
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

void sparkbot::sync()
{
  syncLights();
  syncServos();
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
  analogWrite(BUZZER, value);
}

void sparkbot::stopBuzzer()
{
  analogWrite(BUZZER, 0);
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

void sparkbot::initSlave()
{
  Spark.subscribe("syncServos", (EventHandler)&sparkbot::syncServosSlave, MY_DEVICES);
  Spark.subscribe("RGB", (EventHandler)&sparkbot::RGBSlave, MY_DEVICES);
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

void sparkbot::startLeftButton()
{
attachInterrupt(LEFTBUTTON, (voidFuncPtr)&sparkbot::switchLights, RISING);
}

void sparkbot::startRightButton()
{
attachInterrupt(RIGHTBUTTON, (voidFuncPtr)&sparkbot::sync, RISING);
}

int sparkbot::checkOnline(const char *args)
{
  onlineBots = 1;
  Spark.publish("online?");
  return 1;
}

void sparkbot::yesOnline()
{
  Spark.publish("yesOnline");
}

void sparkbot::updateOnline()
{
  onlineBots++;
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
  neckAngle = neckservo.read();
  rightArmAngle = rightservo.read();
  leftArmAngle = leftservo.read();
}
