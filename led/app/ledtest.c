#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include <unistd.h>

void doHelp(void)
{
    printf("Usage:\n");
    printf("ledtest <hex byte> : data bit0 operation 1=>on 0=>off\n");
    printf("ex) ledtest 0x04 ; 3rd LED on\n");
    printf("    ledtest 0x05 ; 3rd and 1st LED on\n");
    printf("    ledtest 0xff ; all LEDs on\n");
    printf("    ledtest 0x00 ; all LEDs off\n");
}

int main(int argc, char **argv)
{
    unsigned int data = 0;

    if (argc < 2) {
        fprintf(stderr, "Args number is less than 2\n");
        doHelp();
        return 1;
    }

    data = (unsigned int)strtol(argv[1], NULL, 16);
    printf("write data : 0x%X\n", data);

    if (ledLibInit() < 0) {
        fprintf(stderr, "Driver open error\n");
        return -1;
    }

    for (int i = 0; i < 8; i++) {
        int on = (data >> i) & 1;
        ledOnOff(i);
    }

    sleep(2);

    ledLibExit();

    return 0;
}

