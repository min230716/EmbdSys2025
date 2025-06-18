#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"

void doHelp(void) {
    printf("usage: textlcdtest <linenum> <'string'>\n");
    printf("       linenum => 1 ~ 2\n");
    printf("  ex) textlcdtest 2 'test hello'\n");
}

void TextLCD_write(const char* line1, const char* line2)
{
    FILE *fp = fopen("/dev/textlcd", "w");
    if (fp == NULL) {
        perror("TextLCD_write: /dev/textlcd open failed");
        return;
    }

    // 줄바꿈 없이 고정 폭 출력 (예: 16자 LCD 기준)
    char buffer[33] = {0};
    snprintf(buffer, 17, "%-16s", line1); // 1줄 16자
    snprintf(buffer + 16, 17, "%-16s", line2); // 2줄 16자

    fwrite(buffer, 1, 32, fp);
    fclose(fp);
}
