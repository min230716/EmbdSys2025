#ifndef FND_H
#define FND_H

#include "fnddrv.h"

#define FND_DRIVER_NAME         "/dev/perifnd"
#define ONE_SEG_DISPLAY_TIME_USEC       1000
void FND_displayAmmo(int ammo);
int fndDisp(int num, int dotflag);
int fndOff(void);

#endif
