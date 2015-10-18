// main.cpp  This is the barebones required code to use the SparkBot library in a sketch.
// This is a reference document, as it is heavily commented.  Obviously anything commented
// here is not essential for a barebones sketch.
// Written by Nathan Robinson under GPL 3.0
#include "application.h"
#include "sparkbot-default.h" // Import the sparkbot-default library.

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
  Particle.publish("toggleWemo");
}

void setup() // Mandatory setup function.
{
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

"onlineBots", returns the number of online SparkBots, checkOnline() must be called first to update the number.

<FUNCTIONS>

"moveNeck", Calls moveNeckCloud(int), integer from 0-180
"moveRight", Calls moveRightCloud(int), integer from 0-180
"moveLeft", Calls moveLeftCloud(int), integer from 0-180
"moodlights", Calls moodlightsCloud(red, green, blue), 3 RGB values from 0-255

"checkOnline", Calls the checkOnline function, which updates "onlineBots".

*/
sb.moveNeck(90);
sb.moveLeft(90);
sb.moveRight(90);
}


void loop() // Mandatory loop function.
{
  if (digitalRead(I4) == HIGH)
  {
      webhookHandler();
      delay(250);

  }
// sb.playBuzzer(100);
  sb.refresh(); // This function refreshes the arm variables and the brightness variable.
//  analogWrite(REDLED, 250);
  /*
  delay(1500);
  if (sb.moveNeck(0));
  delay(1500);
  if (sb.moveRight(0));
  delay(1500);
  if (sb.moveLeft(0));
  delay(1500);
  if (sb.moveNeck(180));
  delay(1500);
  if (sb.moveRight(180));
  delay(1500);
  if (sb.moveLeft(180));
*/

}
