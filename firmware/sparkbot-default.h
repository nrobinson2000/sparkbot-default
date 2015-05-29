#ifndef sparkbot_default_h
#define sparkbot_default_h

class sparkbot
{
private:
  //Nothing

public:

  sparkbot();

  #define RIGHTBUTTON D7
  #define LEFTBUTTON D3

  #define REDLED D0
  #define BLUELED D1
  #define GREENLED D2

  #define PHOTORESISTOR A5
  #define MICROPHONE A3
  #define BUZZER A4

  #define IO1 A9
  #define IO2 A8
  #define IO3 A7
  #define IO4 A2
  #define IO5 A1
  #define IO6 A0


  #define RIGHTSERVO D4
  #define LEFTSERVO D5
  #define NECKSERVO D6

  int neckAngle;
  int rightArmAngle;
  int leftArmAngle;

  bool redledOn;
  bool blueledOn;
  bool greenledOn;

  int choice;

  void startup(); // Enable servos and pins

  void switchLights();
  void red();
  void blue();
  void green();

  void syncLights();
  void syncServos();

  void moveNeck(int value);
  void moveRight(int value);
  void moveLeft(int value);

  void playBuzzer(int value);
  void stopBuzzer();

  void syncServosSlave(const char *event, const char *data);

  void RGBSlave(const char *event, const char *data);
  void initiateSlave();
  float getTempC(int pin);
  void sync();
  void startLeftButton();
  void startRightButton();

  int moveNeckCloud(const char *data);
  int moveRightCloud(const char *data);
  int moveLeftCloud(const char *data);

  int sparkbotsOnline();
  int moodlights(int red, int blue, int green);

};
#endif
