#include <stdio.h>
#include <stdlib.h>
#include "buzzer.h"

void doHelp(void)
{
    printf("Usage:\n");
    printf("buzzertest <buzzerNo>\n");
    printf("buzzerNo:\n");
    printf("do(1), re(2), mi(3), fa(4), sol(5), ra(6), si(7), do(8)\n");
    printf("off(0)\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        doHelp();
        return 1;
    }

    if (buzzerInit() < 0) {
        fprintf(stderr, "Failed to init buzzer\n");
        return 1;
    }

    int scale = atoi(argv[1]);
    if (scale == 0) {
        buzzerStopSong();
    } else {
        if (buzzerPlaySong(scale) < 0) {
            fprintf(stderr, "Failed to play buzzer\n");
        }
    }

    buzzerExit();
    return 0;
}

