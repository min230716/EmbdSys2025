#ifndef __COLORLED_H__
#define __COLORLED_H__

#define RED_INDEX               0
#define GREEN_INDEX             1
#define BLUE_INDEX              2

#define PWM_FREQUENCY           100000
#define MAX_INPUT_VALUE         100

// 함수 선언만!
int colorLedInit(int red, int green, int blue);
int colorLedExit(void);
void pwmActivatePublic(int bActivate, int pwmIndex);
void pwmEnablePublic(int bEnable, int pwmIndex);
void writePWMPeriodPublic(int frequency, int pwmIndex);
void writePWMDutyPublic(int dutyCycle, int pwmIndex);

#endif

