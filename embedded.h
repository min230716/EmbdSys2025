#ifndef EMBEDDED_H
#define EMBEDDED_H

#include <fcntl.h>  // O_RDWR 상수 정의 추가
#include <unistd.h> // write 함수 선언 추가

// 버튼 관련 함수
int buttonLibInit(void);
int buttonLibExit(void);
int buttonGetStatus(void);

// 부저 관련 함수
int buzzerInit(void);
int buzzerExit(void);
int buzzerPlaySong(int scale);
int buzzerStopSong(void);

// 컬러 LED 관련 함수
void pwmActivatePublic(int bActivate, int pwmchipIndex);
void pwmEnablePublic(int bEnable, int pwmchipIndex);
void writePWMPeriodPublic(int frequency, int pwmchipIndex);
void writePWMDutyPublic(int DutyCycle, int pwmchipIndex);
// colorled.c에서 사용하는 상수 정의
#define RED_INDEX    0
#define GREEN_INDEX  1
#define BLUE_INDEX   2

// FND 관련 함수
int fndDisp(int num, int dotflag);
int fndOff(void);

// LED 관련 함수
int ledLibInit(void);
int ledLibExit(void);
int ledOnOff(int ledNum, int onOff);

// 온도 센서 관련 함수
int spi_initc(const char *filename);
char *spi_read_lm74(int file);

// 텍스트 LCD 관련 함수
// 텍스트 LCD 구조체 수정 (부호 없는 char → 일반 char)
typedef struct {
    int cmd;
    int cmdData;
    char TextData[2][16];  // unsigned char → char로 변경
} stTextLCD;

#define CMD_WRITE_STRING 1
#define CMD_DATA_WRITE_LINE_1 1
#define CMD_DATA_WRITE_LINE_2 2
void doHelp(void);

// 자이로 센서 관련 함수
int gyroInit(void);
float getGyroX(void);
float getGyroY(void);
float getGyroZ(void);

#endif
