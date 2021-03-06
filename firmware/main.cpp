// main.cpp  This is the barebones required code to use the SparkBot library in a sketch.
// This is a reference document, as it is heavily commented.  Obviously anything commented
// here is not essential for a barebones sketch.
// Written by Nathan Robinson under GPL 3.0
#include "application.h"
#include "sparkbot-default.h" // Import the sparkbot-default library.
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
STARTUP(setup());
String readString;

sparkbot sb; // Create sb, an object of the sparkbot class.

void syncServosHandler(const char *event, const char *data)
{
  sb.syncServosSlave(event, data);
}

void RGBSlaveHandler(const char *event, const char *data)
{
sb.RGBSlave(event, data);
}

void webhookHandler()
{
  // Particle.publish("ATC-Bot", "Hello", PRIVATE);
  // Particle.publish("toggleWemo");
}

void setup() // Mandatory setup function.
{
  Particle.connect();
  sb.begin();
  interrupts();

  Particle.subscribe("syncServos", &syncServosHandler, MY_DEVICES);
  Particle.subscribe("RGB", &RGBSlaveHandler, MY_DEVICES);

  sb.moveNeck(90);
  sb.moveLeft(90);
  sb.moveRight(90);
  sb.moodlights(0, 0, 0);
  pinMode(I0, OUTPUT);
  pinMode(I4, INPUT);

}

void parseCommand(String cmd)
{
  Serial.println(cmd);
  if (cmd.startsWith("servos"))
  {
    sb.neckAngle = cmd.substring(7,10).toInt();
    sb.leftArmAngle = cmd.substring(11,14).toInt();
    sb.rightArmAngle = cmd.substring(15,18).toInt();
  }

  if (cmd.startsWith("neck"))
  {
    sb.neckAngle = cmd.substring(5).toInt();
  }

  if (cmd.startsWith("left"))
  {
    sb.leftArmAngle = cmd.substring(5).toInt();
  }

  if (cmd.startsWith("right"))
  {
    sb.rightArmAngle = cmd.substring(6).toInt();
  }
}

void loop() // Mandatory loop function.
{
  sb.refresh();

}
