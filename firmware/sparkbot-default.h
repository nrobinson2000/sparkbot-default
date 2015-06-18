#ifndef sparkbot_default_h
#define sparkbot_default_h

class sparkbot
{
private:
  //Nothing

public:

  sparkbot();

  #define RIGHTBUTTON D7    //<photon pins>
  #define LEFTBUTTON D3           //
                                  //
  #define REDLED D0               //
  #define BLUELED D1              //
  #define GREENLED D2             //
                                  //
  #define PHOTORESISTOR A5        //
  #define MICROPHONE A3           //
  #define BUZZER A4               //
                                  //
  #define IO1 A9                  //
  #define IO2 A8                  //
  #define IO3 A7                  //
  #define IO4 A2                  //
  #define IO5 A1                  //
  #define IO6 A0                  //
                                  //
                                  //
  #define RIGHTSERVO D4           //
  #define LEFTSERVO D5            //
  #define NECKSERVO D6      //</photon pins>


  int neckAngle;            //<variables>
  int rightArmAngle;              //
  int leftArmAngle;               //
                                  //
  int brightness;                 //
                                  //
  bool redledOn;                  //
  bool blueledOn;                 //
  bool greenledOn;                //
                                  //
  int choice;                     //
                                  //
  int onlineBots;           //</variables>

  void begin(); // Enable servos and pins

  void switchLights(); // Cycle through the lights
  void red();          // Turn the lights red
  void blue();         // Turn the lights blue
  void green();        // Turn the lights green
  int moodlights(const char *red, const char *green, const char *blue);

  void syncLights();   // Master command: Sync lights with slaves.
  void syncServos();   // Master command: Sync servos with slaves.
  void sync();

  void moveNeck(int value);
  void moveRight(int value);
  void moveLeft(int value);

  void playBuzzer(int value);
  void stopBuzzer();

  void initSlave();
  void syncServosSlave(const char *event, const char *data);
  void RGBSlave(const char *event, const char *data);

  void startLeftButton();
  void startRightButton();

  int moveNeckCloud(const char *data);
  int moveRightCloud(const char *data);
  int moveLeftCloud(const char *data);

  int checkOnline(const char *args);
  void yesOnline();
  void updateOnline();

  float getTempC(int pin);
  int lightness();
  void refresh();

};
#endif
