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




#endif
