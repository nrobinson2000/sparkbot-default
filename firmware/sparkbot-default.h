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
  #define LED D3               //
  // #define BLUELED A7              //
  // #define GREENLED TX             //
                                  //
  #define PHOTORESISTOR A0        //
  #define MICROPHONE A3           //
  #define BUZZER D0               //
                                  //
  #define I0 A4                   //
  #define I1 A5                   //
  #define I2 A6                   //
  #define I3 A1                   //
  #define I4 A2                   //
  #define I5 D5                   //
  #define I6 D4                   //
                                  //
  //                                 //
  // #define RIGHTSERVO D0           //
  // #define LEFTSERVO D1            //
  // #define NECKSERVO D2      //</photon pins>


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
  int noiseLevel;           //</variables>


  bool slaveMode;

  int moveWrapper(String data);

  void begin(); // Enable servos and pins

  void switchLights(); // Cycle through the lights
  void red();          // Turn the lights red
  void blue();         // Turn the lights blue
  void green();        // Turn the lights green
  void off();
  int moodlightsCloud(String data);
  void moodlights(int red, int green, int blue);

  void syncLights();   // Master command: Sync lights with slaves.
  void syncServos();   // Master command: Sync servos with slaves.
  void sync();

  String makeProper(int value);
  void moveNeck(int value);
  void moveRight(int value);
  void moveLeft(int value);

  void playBuzzer(int value);
  void stopBuzzer();
  int soundCloud(String data);

  void syncServosSlave(const char *event, const char *data);
  void RGBSlave(const char *event, const char *data);

  int slaveToggle(String data);

  void startLeftButton();
  void startRightButton();


  int moveCloud(String data);

  float getTempC(int pin);
  int lightness();
  int getNoiseLevel();
  void refresh();

  void command(const char *data);
  String readData();

  int askNeck();
  int askLeft();
  int askRight();
};
#endif
