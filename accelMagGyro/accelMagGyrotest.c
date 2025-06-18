#include <stdio.h>
#include "accelMagGyro.h"

int main(void)
{
    int x, y, z;

    if (readAccel(&x, &y, &z) == 0)
        printf("I read Accel     %d, %d, %d\n", x, y, z);
    else
        printf("Accel read failed\n");

    if (readMagneto(&x, &y, &z) == 0)
        printf("I read Magneto   %d, %d, %d\n", x, y, z);
    else
        printf("Magneto read failed\n");

    if (readGyro(&x, &y, &z) == 0)
        printf("I read Gyroscope %d, %d, %d\n", x, y, z);
    else
        printf("Gyro read failed\n");

    return 0;
}

