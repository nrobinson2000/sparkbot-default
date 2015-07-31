#include "application.h"
#ifndef sparkbot_default_h
#define sparkbot_default_h

class sparkbot
{
private:
  //Nothing

public:

  sparkbot();

  #define RIGHTBUTTON D7    //<photon pins>
  #define LEFTBUTTON D6           //
                                  //
  #define REDLED D3               //
  #define BLUELED A5              //
  #define GREENLED A7             //
                                  //
  #define PHOTORESISTOR A0        //
  #define MICROPHONE A3           //
  #define BUZZER A4               //
                                  //
  #define I0 A6                   //
  #define I1 A1                   //
  #define I2 A2                   //
  #define I3 D5                   //
  #define I5 D4                   //
                                  //
                                  //
  #define RIGHTSERVO D0           //
  #define LEFTSERVO D1            //
  #define NECKSERVO D2      //</photon pins>


  int neckAngle;            //<variables>
  int rightArmAngle;              //
  int leftArmAngle;               //
                                  //
  int brightness;                 //
                                  //
  int redValue;                   //
  int greenValue;                 //
  int blueValue;                  //
                                  //
  int choice;                     //
                                  //
  int onlineBots;           //</variables>

  bool slaveMode;

  void begin(); // Enable servos and pins

  void switchLights(); // Cycle through the lights
  void red();          // Turn the lights red
  void blue();         // Turn the lights blue
  void green();        // Turn the lights green
  int moodlightsCloud(String red, String green, String blue);
  void moodlights(int red, int green, int blue);

  void syncLights();   // Master command: Sync lights with slaves.
  void syncServos();   // Master command: Sync servos with slaves.
  void sync();

  void moveNeck(int value);
  void moveRight(int value);
  void moveLeft(int value);

  void playBuzzer(int value);
  void stopBuzzer();

  void syncServosSlave(const char *event, const char *data);
  void RGBSlave(const char *event, const char *data);

  int slaveToggle(String data);

  void startLeftButton();
  void startRightButton();

  int moveNeckCloud(String data);
  int moveRightCloud(String data);
  int moveLeftCloud(String data);

  float getTempC(int pin);
  int lightness();
  void refresh();
};
#endif
