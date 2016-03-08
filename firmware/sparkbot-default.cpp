#include "sparkbot-default.h"
#include "application.h"

sparkbot::sparkbot()
{
  // 3 Servo angles
  neckAngle = 0;
  leftArmAngle = 0;
  rightArmAngle = 0;

  redValue = 0;
  greenValue = 0;
  blueValue = 0;

  choice = 0; // Used for switching lights

  slaveMode = false;
}

void sparkbot::begin()
{
  pinMode(RIGHTBUTTON, INPUT);  //We Enable the inputs.
  pinMode(LEFTBUTTON, INPUT);
  pinMode(PHOTORESISTOR, INPUT);
  pinMode(MICROPHONE, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

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
  Particle.variable("noise", &noiseLevel, INT);

  auto moveHandler = std::bind(&sparkbot::moveCloud, this, std::placeholders::_1);
  Particle.function("moveServos", moveHandler);

  auto moodHandler = std::bind(&sparkbot::moodlightsCloud, this, std::placeholders::_1);
  Particle.function("moodlights", moodHandler);

  auto slaveHandler = std::bind(&sparkbot::slaveToggle, this, std::placeholders::_1);
  Particle.function("enableSlave", slaveHandler);

  auto soundHandler = std::bind(&sparkbot::soundCloud, this, std::placeholders::_1);
  Particle.function("playSound", soundHandler);

  Serial.begin(9600);
  Serial1.begin(9600);
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
  command("rgb 255 000 000");
  redValue = 255;
  greenValue = 0;
  blueValue = 0;
}

void sparkbot::green() //This function turns on the green, and turns off the red and blue
{
  command("rgb 000 255 000");
  redValue = 000;
  greenValue = 255;
  blueValue = 0;
}

void sparkbot::blue() //This function turns on the blue, and turns off the red and green
{
  command("rgb 000 000 255");
  redValue = 0;
  greenValue = 0;
  blueValue = 255;
}

void sparkbot::off()
{
  command("rgb 000 000 000");
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
}

int sparkbot::moodlightsCloud(String data)
{
  command("rgb " + data);
  String red = data.substring(0, 3);
  String green = data.substring(4, 7);
  String blue = data.substring(8,11);

  redValue = red.toInt();
  greenValue = green.toInt();
  blueValue = blue.toInt();

  Serial.println("Original String:" + data);
  Serial.println("RED:" + String(red.toInt()));
  Serial.println("GREEN:" + String(green.toInt()));
  Serial.println("BLUE:" + String(blue.toInt()));
  return 1;
}

void sparkbot::moodlights(int red, int green, int blue)
{
  command("rgb " + String(red) + " " + String(green) + " " + String(blue));
  redValue = red;
  greenValue = green;
  blueValue = blue;
}

void sparkbot::syncLights()
{
  String color;
  color.concat(makeProper(redValue));
  color.concat(" ");
  color.concat(makeProper(greenValue));
  color.concat(" ");
  color.concat(makeProper(blueValue));
  Particle.publish("RGB", color);
}

void sparkbot::syncServos()
{
  String message = String("");
  String neckdata = String("");
  String leftdata = String("");
  String rightdata = String("");

  String neckString = String(askNeck());
  String leftString = String(askLeft());
  String rightString = String(askRight());

  int neck = neckString.toInt();
  int left = leftString.toInt();
  int right = rightString.toInt();

  bool neckchanged = false;
  bool leftchanged = false;
  bool rightchanged = false;

  if (neckAngle != neck)
  {
    neckAngle = neck;
    neckchanged = true;
    neckdata = makeProper(neck);
  }

  if (leftArmAngle != left)
  {
    leftArmAngle = left;
    leftchanged = true;
    leftdata = makeProper(left);
  }

  if (rightArmAngle != right)
  {
    rightArmAngle = right;
    rightchanged = true;
    rightdata = makeProper(right);
  }

switch (neckchanged)
{
  case true:
  message += neckdata;
  break;

  case false:
  message += String("200");
}

switch (leftchanged)
{
  case true:
  message += leftdata;
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

  Particle.publish("syncServos", message);
}

void sparkbot::sync()
{
  syncLights();
  syncServos();
}

String sparkbot::makeProper(int value)
{
  String valuedata;
  if (value < 100 && value > 9)
  {
    valuedata = String("0" + String(value));
  }
  if (value < 10)
  {
    valuedata = String("00" +String(value));
  }
  else
  {
    valuedata = String(value);
  }

  return valuedata;
}

void sparkbot::moveNeck(int value)
{
  String valuedata = makeProper(value);

  String message = String("moveNeck ");
  message.concat(valuedata);
  command(message);
  delay(50);
}

void sparkbot::moveLeft(int value)
{
  String valuedata = makeProper(value);

  String message = String("moveLeft ");
  message.concat(valuedata);
  command(message);
  delay(50);
}

void sparkbot::moveRight(int value)
{
  String valuedata = makeProper(value);

  String message = String("moveRight ");
  message.concat(valuedata);
  command(message);
  delay(50);
}

void sparkbot::playBuzzer(int value)
{
  analogWrite(BUZZER, value);
}

void sparkbot::stopBuzzer()
{
  analogWrite(BUZZER, 0);
}

int sparkbot::soundCloud(String data)
{
  playBuzzer(data.toInt());
  return 1;
}

int sparkbot::moveCloud(String data)
{
  String neckvalue = data.substring(0, 3);
  String leftvalue = data.substring(4, 7);
  String rightvalue = data.substring(8,11);

  if (neckvalue.toInt() != 200)
  {
    moveNeck(neckvalue.toInt());
  }

  if (leftvalue.toInt() != 200)
  {
    moveLeft(leftvalue.toInt());
  }

  if (rightvalue.toInt() != 200)
  {
    moveRight(rightvalue.toInt());
  }

  Serial.println("Original String: " + data);
  Serial.println("Neck: " + String(neckvalue.toInt()));
  Serial.println("Left: " + String(leftvalue.toInt()));
  Serial.println("Right: " + String(rightvalue.toInt()));
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
  String leftresult = message.substring(3, 6);
  String rightresult = message.substring(6,9);

  bool moveNeck = false;
  bool moveRight = false;
  bool moveLeft = false;

  if (neckresult.toInt() >= 0 && neckresult.toInt() <= 180)
  {
    moveNeck = true;
  }

  if (leftresult.toInt() >= 0 && leftresult.toInt() <= 180)
  {
    moveLeft = true;
  }

  if (rightresult.toInt() >= 0 && rightresult.toInt() <= 180)
  {
    moveRight = true;
  }


  if (moveNeck == true)
  {
    sparkbot::moveNeck(neckresult.toInt());
  }

  if (moveLeft == true)
  {
    sparkbot::moveLeft(leftresult.toInt());
  }

  if (moveRight == true)
  {
    sparkbot::moveRight(rightresult.toInt());
  }

}

void sparkbot::RGBSlave(const char *event, const char *data)
{
  if (slaveMode == false) {return;}
  moodlightsCloud(data);
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

int sparkbot::getNoiseLevel()
{
  return analogRead(MICROPHONE) / 4;
}

void sparkbot::refresh()
{
  brightness = lightness();
  noiseLevel = getNoiseLevel();
}

void sparkbot::command(const char *data)
{
  Serial1.println(data);
}

String sparkbot::readData()
{
  String readString;

  while (Serial1.available())
  {
    delay(3);
    char c = Serial1.read();
    readString += c;
  }

  readString.trim();

  if (readString.length() >0)
  {
    return readString;
  }
}

int sparkbot::askNeck()
{
command("neck");
delay(50);
return readData().toInt();
}

int sparkbot::askLeft()
{
command("left");
delay(50);
return readData().toInt();
}

int sparkbot::askRight()
{
  command("right");
  delay(50);
  return readData().toInt();
}
