#ifndef __ACCEL_MAG_GYRO_H__
#define __ACCEL_MAG_GYRO_H__

int readAccel(int *x, int *y, int *z);
int readMagneto(int *x, int *y, int *z);
int readGyro(int *x, int *y, int *z);



int gyroInit(void);
float getGyroX(void);
float getGyroY(void);
float getGyroZ(void);
#endif

