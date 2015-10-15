[![Build Status](https://travis-ci.org/nrobinson2000/sparkbot-default.svg?branch=master)](https://travis-ci.org/nrobinson2000/sparkbot-default)
#sparkbot-default

##About:
* This is the default library for the SparkBot by Nathan Robinson.  This library contains all of the necessary functions and variables to make using SparkBot easier.

## Basic Usage:
    #include "sparkbot-default.h" // Import the sparkbot-default library.

    sparkbot sb; // Create sb, an object of the sparkbot class.

    sb.begin(); // This initializes the SparkBot.

##Additional processes:  

    sb.sync(); // Master sync command.  Sync other slave bots to the settings of this SparkBot.

    sb.startLeftButton(); // Start the light switching process.

    sb.startRightButton(); // Start the Master bot process.

    sb.refresh(); //refreshes cloud variables, should be run in loop.

##SparkBot cloud Variables:

    "neck", returns the neckAngle of NECKSERVO
    "rightArm", returns the rightArmAngle of RIGHTSERVO
    "leftArm", returns the leftArmAngle LEFTSERVO
    "brightness", returns the brightness of PHOTORESISTOR

##SparkBot cloud Functions:

    "moveServos", must be a string like this "NNN RRR LLL", writes values to the servos.
    "moodlights", must be a string like this "RRR GGG BBB", writes values to the moodlights.
    "enableSlave", toggles whether or not this is a slave bot
