#ifndef sparkbot_default_h
#define sparkbot_default_h

class sparkbot
{
private:
  //Nothing

public:

  sparkbot();

  int neckAngle;
  int rightArmAngle;
  int leftArmAngle;

  int rightbutton;
  int leftbutton;

  int redled;
  int blueled;
  int greenled;

  bool redledOn;
  bool blueledOn;
  bool greenledOn;

  int temperature;
  int microphone;

  int buzzer;

  int io1;
  int io2;
  int io3;
  int io4;
  int io5;
  int io6;

  int rightServoPin;
  int leftServoPin;
  int neckServoPin;

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
  float getTempC();
  void sync();
  void startLeftButton();
  void startRightButton();

  int moveNeckCloud(const char *data);
  int moveRightCloud(const char *data);
  int moveLeftCloud(const char *data);

};
#endif
