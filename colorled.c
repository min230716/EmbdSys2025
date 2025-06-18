#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "colorled.h"

#define MAX_INPUT_VALUE        100
#define PWM_BASE_SYS_PATH      "/sys/class/pwm/pwmchip"
#define PWM_ENABLE_NAME        "enable"
#define PWM_FREQUENCY_NAME     "period"
#define PWM_DUTYCYCLE_NAME     "duty_cycle"
#define PWM_CHANNEL_NUM        0  // 항상 pwm0 채널 사용

// 공통 함수: 경로에 값 쓰기
static void writeToFile(const char* path, const char* value)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        perror(path);
        return;
    }
    fprintf(fp, "%s", value);
    fclose(fp);
}

// PWM export/unexport
void pwmActivatePublic(int bActivate, int pwmChipIndex)
{
    char path[100], value[10];
    sprintf(path, "%s%d/%s", PWM_BASE_SYS_PATH, pwmChipIndex, bActivate ? "export" : "unexport");
    sprintf(value, "%d", PWM_CHANNEL_NUM);
    writeToFile(path, value);
}

// PWM enable
void pwmEnablePublic(int bEnable, int pwmChipIndex)
{
    char path[150], value[10];
    sprintf(path, "%s%d/pwm%d/%s", PWM_BASE_SYS_PATH, pwmChipIndex, PWM_CHANNEL_NUM, PWM_ENABLE_NAME);
    sprintf(value, "%d", bEnable);
    writeToFile(path, value);
}

// PWM period 설정
void writePWMPeriodPublic(int frequency, int pwmChipIndex)
{
    char path[150], value[20];
    sprintf(path, "%s%d/pwm%d/%s", PWM_BASE_SYS_PATH, pwmChipIndex, PWM_CHANNEL_NUM, PWM_FREQUENCY_NAME);
    sprintf(value, "%d", frequency);
    writeToFile(path, value);
}

// PWM duty cycle 설정
void writePWMDutyPublic(int dutyCycle, int pwmChipIndex)
{
    char path[150], value[20];
    sprintf(path, "%s%d/pwm%d/%s", PWM_BASE_SYS_PATH, pwmChipIndex, PWM_CHANNEL_NUM, PWM_DUTYCYCLE_NAME);
    sprintf(value, "%d", dutyCycle);
    writeToFile(path, value);
}

// 컬러 LED 초기화
int colorLedInit(int red, int green, int blue)
{
    if (red < 0 || red > MAX_INPUT_VALUE ||
        green < 0 || green > MAX_INPUT_VALUE ||
        blue < 0 || blue > MAX_INPUT_VALUE)
        return -1;

    red = MAX_INPUT_VALUE - red;
    green = MAX_INPUT_VALUE - green;
    blue = MAX_INPUT_VALUE - blue;

    int redDuty = PWM_FREQUENCY * red / MAX_INPUT_VALUE;
    int greenDuty = PWM_FREQUENCY * green / MAX_INPUT_VALUE;
    int blueDuty = PWM_FREQUENCY * blue / MAX_INPUT_VALUE;

    pwmActivatePublic(1, RED_INDEX);
    writePWMPeriodPublic(PWM_FREQUENCY, RED_INDEX);
    writePWMDutyPublic(redDuty, RED_INDEX);
    pwmEnablePublic(1, RED_INDEX);

    pwmActivatePublic(1, GREEN_INDEX);
    writePWMPeriodPublic(PWM_FREQUENCY, GREEN_INDEX);
    writePWMDutyPublic(greenDuty, GREEN_INDEX);
    pwmEnablePublic(1, GREEN_INDEX);

    pwmActivatePublic(1, BLUE_INDEX);
    writePWMPeriodPublic(PWM_FREQUENCY, BLUE_INDEX);
    writePWMDutyPublic(blueDuty, BLUE_INDEX);
    pwmEnablePublic(1, BLUE_INDEX);

    return 0;
}

// 컬러 LED 종료
int colorLedExit()
{
    pwmEnablePublic(0, RED_INDEX);
    pwmEnablePublic(0, GREEN_INDEX);
    pwmEnablePublic(0, BLUE_INDEX);

    pwmActivatePublic(0, RED_INDEX);
    pwmActivatePublic(0, GREEN_INDEX);
    pwmActivatePublic(0, BLUE_INDEX);
    return 0;
}

