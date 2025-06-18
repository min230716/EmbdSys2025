#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH  "/sys/class/misc/FreescaleGyroscope/"

static int enableSensor(const char *path) {
    int fd = open(path, O_WRONLY);
    if (fd < 0) return -1;
    dprintf(fd, "1");
    close(fd);
    return 0;
}

static int readSensorData(const char *path, int *x, int *y, int *z) {
    FILE *fp = fopen(path, "rt");
    if (!fp) return -1;
    int ret = fscanf(fp, "%d, %d, %d", x, y, z);
    fclose(fp);
    return (ret == 3) ? 0 : -1;
}

// 초기화 함수: 자이로 센서 활성화
int gyroInit(void) {
    return enableSensor(GYROPATH "enable");
}

// 자이로 센서 각 축 데이터 저장용 static 변수
static int gyro_x = 0, gyro_y = 0, gyro_z = 0;

// 자이로 센서 데이터 읽기 및 저장 (내부 함수)
static void updateGyroData(void) {
    if (readSensorData(GYROPATH "data", &gyro_x, &gyro_y, &gyro_z) < 0) {
        gyro_x = gyro_y = gyro_z = 0;
    }
}

// 각각 X, Y, Z 축 값 리턴 함수
float getGyroX(void) {
    updateGyroData();
    return (float)gyro_x;
}

float getGyroY(void) {
    updateGyroData();
    return (float)gyro_y;
}

float getGyroZ(void) {
    updateGyroData();
    return (float)gyro_z;
}
// 가속도계 데이터 읽기
int readAccel(int *x, int *y, int *z) {
    return readSensorData(ACCELPATH "data", x, y, z);
}

// 자기장 센서 데이터 읽기
int readMagneto(int *x, int *y, int *z) {
    return readSensorData(MAGNEPATH "data", x, y, z);
}

// 자이로센서 데이터 읽기
int readGyro(int *x, int *y, int *z) {
    return readSensorData(GYROPATH "data", x, y, z);
}
