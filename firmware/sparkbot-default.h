#ifndef sparkbot_default_h
#define sparkbot_default_h

void startup();
void enableRightButton(const char *handler);
void enableLeftButton(const char *handler);
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
void startSlave();
void moveNeckSlave(const char *event, const char *data);
void moveRightSlave(const char *event, const char *data);
void moveLeftSlave(const char *event, const char *data);
void redLedSlave(const char *event, const char *data);
void blueLedSlave(const char *event, const char *data);
void greenLedSlave(const char *event, const char *data);


#endif
