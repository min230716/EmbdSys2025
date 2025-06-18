#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

#define LED_DRIVER_NAME "/dev/periled"
#define LED_COUNT 8
#define LED_ALL_ON ((1 << LED_COUNT) - 1)  // 0xFF

static unsigned int ledValue = 0;
static int fd = -1;

// 전체 LED를 비트마스크로 제어하는 함수
int ledOnOff(unsigned int value)
{
    if (fd < 0) {
        fprintf(stderr, "LED device not initialized.\n");
        return -1;
    }

    ledValue = value;

    if (write(fd, &ledValue, sizeof(unsigned int)) < 0) {
        perror("write");
        return -1;
    }

    return 0;
}

// LED 장치 초기화 (모든 LED 켜기)
int ledLibInit(void)
{
    fd = open(LED_DRIVER_NAME, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    ledValue = LED_ALL_ON;  // 초기화 시 모든 LED 켜기
    return ledOnOff(ledValue);
}

// LED 장치 종료 (모든 LED 끄기)
int ledLibExit(void)
{
    if (fd < 0) {
        fprintf(stderr, "LED device not opened.\n");
        return -1;
    }

    ledOnOff(0);  // 종료 시 모든 LED 끄기

    if (close(fd) < 0) {
        perror("close");
        return -1;
    }

    fd = -1;
    return 0;
}
void LED_displayHealth(int health)
{
    if (health < 0) health = 0;
    if (health > 100) health = 100;

    unsigned char led_mask = (health * 8) / 100;
    unsigned char value = 0;

    for (int i = 0; i < led_mask; ++i) {
        value |= (1 << i);
    }

    // 예: /dev/led 디바이스 파일에 출력
    FILE *fp = fopen("/dev/led", "w");
    if (fp) {
        fwrite(&value, 1, 1, fp);
        fclose(fp);
    } else {
        perror("LED_displayHealth: /dev/led open failed");
    }
}
