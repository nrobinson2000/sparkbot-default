#ifndef sparkbot_default_h
#define sparkbot_default_h


class sparkbot
{
private:
  //Nothing

public:

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
/*
  void moveNeckSlave(const char *event, const char *data);
  void moveRightSlave(const char *event, const char *data);
  void moveLeftSlave(const char *event, const char *data);
  void redLedSlave(const char *event, const char *data);
  void blueLedSlave(const char *event, const char *data);
  void greenLedSlave(const char *event, const char *data);
  void startSlave();
  */

};
#endif
