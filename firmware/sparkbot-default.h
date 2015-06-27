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
  #define IO1 D4                  //
  #define IO2 A6                  //
  #define IO3 A2                  //
  #define IO4 A1                  //
  #define IO5 D5                  //
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
  int redValue;
  int greenValue;
  int blueValue;              //
                                  //
  int choice;                     //
                                  //
  int onlineBots;           //</variables>

  bool asleep;
  unsigned int lastAwoken;
  unsigned int timeAwake;
  unsigned int sleepInterval;

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
