#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "button.h"
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"


int main(void) {
    if (buttonLibInit() < 0) {
        fprintf(stderr, "buttonLibInit failed\n");
        return -1;
    }

    printf("Button test start. Press Ctrl+C to exit.\n");
    while (1) {
        int status = buttonGetStatus();
        if (status < 0) {
            fprintf(stderr, "Failed to read button status\n");
            break;
        }
        printf("Button status: 0x%x\n", status);
        sleep(1);
    }

    buttonLibExit();
    return 0;
}
