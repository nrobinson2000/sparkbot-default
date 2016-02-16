// main.cpp  This is the barebones required code to use the SparkBot library in a sketch.
// This is a reference document, as it is heavily commented.  Obviously anything commented
// here is not essential for a barebones sketch.
// Written by Nathan Robinson under GPL 3.0
#include "application.h"
#include "sparkbot-default.h" // Import the sparkbot-default library.
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
STARTUP(setup());


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

// This initializes the SparkBot.
//It starts all the pins, servos, cloud variables, functions and subscriptions.

/////Start other SparkBot processes below./////

// sb.initSlave(); // Configure this SparkBot as a slave bot.

// sb.sync(); // Master sync command.  Sync other slave bots to the settings of this SparkBot.

// sb.startLeftButton(); // Start the light switching process.

// sb.startRightButton(); // Start the Master bot process.


/*///CLOUD FUNCTIONS AND VARIABLES/////

<VARIABLES>

"neck", returns the neckAngle of NECKSERVO
"rightArm", returns the rightArmAngle of RIGHTSERVO
"leftArm", returns the leftArmAngle LEFTSERVO
"brightness", returns the brightness of PHOTORESISTOR


<FUNCTIONS>

"moveServos", Calls moveCloud(String data), where data is a string containing values from 000-180 for the neck, left, and right servos.
"moodlights", Calls moodlightsCloud(String data), where data is a string containing values from 000-255 for the red, green, and blue LEDs.
"enableSlave", Toggles slave mode, which makes the robot mimic another.

*/
  sb.moveNeck(90);
  sb.moveLeft(90);
  sb.moveRight(90);

  pinMode(I0, OUTPUT);
  pinMode(I4, INPUT);

  Serial1.println("Hello");
}

void loop() // Mandatory loop function.
{
  sb.refresh();
}
