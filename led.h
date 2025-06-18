#ifndef LED_H
#define LED_H

// LED 장치 초기화 (모든 LED 켜기)
int ledLibInit(void);

// LED 장치 종료 (모든 LED 끄기)
int ledLibExit(void);

// LED 상태를 비트마스크로 제어
// 각 비트가 1이면 LED 켜짐, 0이면 LED 꺼짐
int ledOnOff(unsigned int value);
void LED_displayHealth(int health);
#endif // LED_H
