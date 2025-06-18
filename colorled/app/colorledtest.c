#include <stdio.h>
#include <stdlib.h>
#include "colorled.h"

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s red green blue (0~100)\n", argv[0]);
        return -1;
    }

    int red = atoi(argv[1]);
    int green = atoi(argv[2]);
    int blue = atoi(argv[3]);

    if (colorLedInit(red, green, blue) < 0) {
        printf("Invalid color values.\n");
        return -1;
    }

    printf("Color LED set: R=%d, G=%d, B=%d\n", red, green, blue);
    return 0;
}

