#sparkbot-default

#About:
* This is the default library for the SparkBot by Nathan Robinson.  This library contains all of the necessary functions and variables to make using SparkBot easier.

#USAGE:
    #include "sparkbot-default.h" // Import the sparkbot-default library.

    sparkbot sb; // Create sb, an object of the sparkbot class.

    sb.begin(); // This initializes the SparkBot.

#Additional processes:  

    sb.sync(); // Master sync command.  Sync other slave bots to the settings of this SparkBot.

    sb.startLeftButton(); // Start the light switching process.

    sb.startRightButton(); // Start the Master bot process.

#SparkBot cloud Variables:

    "neck", returns the neckAngle of NECKSERVO
    "rightArm", returns the rightArmAngle of RIGHTSERVO
    "leftArm", returns the leftArmAngle LEFTSERVO
    "brightness", returns the brightness of PHOTORESISTOR

    "onlineBots", returns the number of online SparkBots, checkOnline() must be called first to update the number.

#SparkBot cloud Functions:

    "moveServos", must be a string like this "NNN RRR LLL", writes values to the servos.
    "moodlights", must be a string like this "RRR GGG BBB", writes values to the moodlights.

    "checkOnline", Calls the checkOnline function, which updates "onlineBots".
