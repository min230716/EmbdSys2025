#include "button.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static int buttonFd = -1;
static pthread_t buttonThread;
static int threadRunning = 0;

static int probeButtonPath(char *newPath)
{
    FILE *fp = fopen(PROBE_FILE, "rt");
    if (fp == NULL) return 0;

    char tmpStr[200];
    int found = 0;
    int number = -1;
    while (!feof(fp)) {
        if (fgets(tmpStr, sizeof(tmpStr), fp) == NULL) {
   		 fclose(fp);
		 return -1;
}
        if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
            found = 1;
        if (found && strncmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0) {
            char *p = strstr(tmpStr, "event");
            if (p != NULL) {
                if (sscanf(p, "event%d", &number) == 1) {
                    break;
                }
            }
        }
    }
    fclose(fp);

    if (found && number >= 0) {
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
        return 1;
    }
    return 0;
}

static void* buttonThreadFunction(void *arg)
{
    struct input_event stEvent;
    while (threadRunning) {
        int readSize = read(buttonFd, &stEvent, sizeof(stEvent));
        if (readSize != sizeof(stEvent)) continue;

        if (stEvent.type == EV_KEY) {
            printf("EV_KEY(");
            switch(stEvent.code) {
                case KEY_VOLUMEUP:   printf("Volume up key): "); break;
                case KEY_HOME:       printf("Home key): "); break;
                case KEY_SEARCH:     printf("Search key): "); break;
                case KEY_BACK:       printf("Back key): "); break;
                case KEY_MENU:       printf("Menu key): "); break;
                case KEY_VOLUMEDOWN: printf("Volume down key): "); break;
                default:             printf("Unknown key %d): ", stEvent.code); break;
            }
            if (stEvent.value)
                printf("pressed\n");
            else
                printf("released\n");
        }
    }
    return NULL;
}

int buttonLibInit(void)
{
    char inputDevPath[200] = {0};
    if (!probeButtonPath(inputDevPath)) {
        fprintf(stderr, "ERROR! File Not Found!\nDid you insmod?\n");
        return -1;
    }

    printf("DEBUG: input device path = %s\n", inputDevPath);  // 디버깅용 출력

    buttonFd = open(inputDevPath, O_RDONLY);
    if (buttonFd < 0) {
        perror("open");
        return -1;
    }

    threadRunning = 1;
    if (pthread_create(&buttonThread, NULL, buttonThreadFunction, NULL) != 0) {
        perror("pthread_create");
        close(buttonFd);
        buttonFd = -1;
        return -1;
    }
    return 0;
}

int buttonLibExit(void)
{
    if (buttonFd > 0) {
        threadRunning = 0;
        pthread_join(buttonThread, NULL);
        close(buttonFd);
        buttonFd = -1;
    }
    return 0;
}

int buttonGetStatus(void)
{
    return buttonFd;
}

