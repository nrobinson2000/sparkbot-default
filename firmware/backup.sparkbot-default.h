#ifndef sparkbot_default_h
#define sparkbot_default_h

// Global variables

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


// Functions

void startup();

/* Fix this later
void enableRightButton(voidFuncPtr handler);
void enableLeftButton(voidFuncPtr handler);
*/

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