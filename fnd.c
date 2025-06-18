#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"

void FND_displayAmmo(int ammo)
{
    if (ammo < 0) ammo = 0;
    if (ammo > 99) ammo = 99;

    // 예: 7세그먼트 디바이스 드라이버 파일이 /dev/fnd라고 가정
    FILE *fp = fopen("/dev/fnd", "w");
    if (fp) {
        fprintf(fp, "%02d", ammo);
        fclose(fp);
    } else {
        perror("FND_displayAmmo: /dev/fnd open failed");
    }
}

int fndDisp(int num, int dotflag) {
    int fd;
    int temp,i;
    stFndWriteForm stWriteData;

    for (i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
        stWriteData.DataValid[i] = 1;
    }

    temp = num % 1000000;   stWriteData.DataNumeric[0]= temp /100000;
    temp = num % 100000;    stWriteData.DataNumeric[1]= temp /10000;
    temp = num % 10000;     stWriteData.DataNumeric[2] = temp /1000;
    temp = num %1000;       stWriteData.DataNumeric[3] = temp /100;
    temp = num %100;        stWriteData.DataNumeric[4] = temp /10;
                            stWriteData.DataNumeric[5] = num %10;

    fd = open(FND_DRIVER_NAME,O_RDWR);
    if (fd < 0) {
        perror("driver open error.\n");
        return 0;
    }
    (void)write(fd,&stWriteData,sizeof(stFndWriteForm));
    close(fd);
    return 1;
}

int fndOff() {
    int fd,i;
    stFndWriteForm stWriteData;

    for (i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = 0;
        stWriteData.DataNumeric[i] = 0;
        stWriteData.DataValid[i] = 0;
    }
    fd = open(FND_DRIVER_NAME,O_RDWR);
    if (fd < 0) {
        perror("driver open error.\n");
        return 0;
    }
    (void)write(fd,&stWriteData,sizeof(stFndWriteForm));
    close(fd);
    return 1;
}
