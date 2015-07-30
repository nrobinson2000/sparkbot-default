// main.ino  This is the barebones required code to use the SparkBot library in a sketch.
// This is a reference document, as it is heavily commented.  Obviously anything commented
// here is not essential for a barebones sketch.
// Written by Nathan Robinson under GPL 3.0

#include "sparkbot-default.h" // Import the sparkbot-default library.

sparkbot sb; // Create sb, an object of the sparkbot class.
int tinkerDigitalRead(String pin);
int tinkerDigitalWrite(String command);
int tinkerAnalogRead(String pin);
int tinkerAnalogWrite(String command);

void setup() // Mandatory setup function.
{
  Spark.function("digitalread", tinkerDigitalRead);
    Spark.function("digitalwrite", tinkerDigitalWrite);
    Spark.function("analogread", tinkerAnalogRead);
    Spark.function("analogwrite", tinkerAnalogWrite);
sb.begin(); // This initializes the SparkBot.
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
}




int tinkerDigitalRead(String pin)
{
    int pinNumber = pin.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    if(pin.startsWith("D"))
    {
        pinMode(pinNumber, INPUT_PULLDOWN);
        return digitalRead(pinNumber);
        }
    else if (pin.startsWith("A"))
    {
        pinMode(pinNumber+10, INPUT_PULLDOWN);
        return digitalRead(pinNumber+10);
        }
    return -2;
}

int tinkerDigitalWrite(String command)
{
    bool value = 0;
    int pinNumber = command.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    if(command.substring(3,7) == "HIGH") value = 1;
    else if(command.substring(3,6) == "LOW") value = 0;
    else return -2;
    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, value);
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        digitalWrite(pinNumber+10, value);
        return 1;
    }
    else return -3;
}

int tinkerAnalogRead(String pin)
{
    int pinNumber = pin.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    if(pin.startsWith("D"))
    {
        pinMode(pinNumber, INPUT);
        return analogRead(pinNumber);
    }
    else if (pin.startsWith("A"))
    {
        pinMode(pinNumber+10, INPUT);
        return analogRead(pinNumber+10);
    }
    return -2;
  }

int tinkerAnalogWrite(String command)
{
    int pinNumber = command.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1;
    String value = command.substring(3);
    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        analogWrite(pinNumber, value.toInt());
        return 1;
        }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        analogWrite(pinNumber+10, value.toInt());
        return 1;
    }
    else return -2;
  }

void loop() // Mandatory loop function.
{
sb.refresh(); // This function refreshes the arm variables and the brightness variable.

}
