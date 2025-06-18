#include "buzzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define PATH_MAX_LEN 600  // 충분히 크게 잡기
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

static char gBuzzerBaseSysDir[512];  // 넉넉하게 버퍼 크기 설정
const int musicScale[MAX_SCALE_STEP] = {
    262, 294, 330, 349, 392, 440, 494, 523
};

// 버저 디바이스 경로 탐색
static int findBuzzerSysPath(void) {
    DIR *dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;

    if (dir_info != NULL) {
        while (1) {
            struct dirent *dir_entry;
            dir_entry = readdir(dir_info);
            if (dir_entry == NULL) break;

            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0) {
                ifNotFound = 0;
                snprintf(gBuzzerBaseSysDir, sizeof(gBuzzerBaseSysDir),
                         "%s%s/", BUZZER_BASE_SYS_PATH, dir_entry->d_name);
                break;
            }
        }
        closedir(dir_info);
    }

    if (!ifNotFound) {
        printf("Buzzer device path: %s\n", gBuzzerBaseSysDir);
    }

    return ifNotFound;
}

// 초기화
int buzzerInit(void) {
    return findBuzzerSysPath();
}

// 종료 처리 (현재는 아무 작업 없음)
int buzzerExit(void) {
    return 0;
}

// 노래 재생 (스케일 설정 및 활성화)
int buzzerPlaySong(int scale) {
    if (scale < 1 || scale > MAX_SCALE_STEP) {
        fprintf(stderr, "Invalid scale\n");
        return -1;
    }

    char freqPath[PATH_MAX_LEN];
    char enablePath[PATH_MAX_LEN];

    snprintf(freqPath, sizeof(freqPath), "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    snprintf(enablePath, sizeof(enablePath), "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);

    int freqFd = open(freqPath, O_WRONLY);
    if (freqFd < 0) {
        perror("open freqPath");
        return -1;
    }
    dprintf(freqFd, "%d", musicScale[scale - 1]);
    close(freqFd);

    int enableFd = open(enablePath, O_WRONLY);
    if (enableFd < 0) {
        perror("open enablePath");
        return -1;
    }
    if (write(enableFd, "1", 1) != 1) {
   	 perror("write");
   	 close(enableFd);
	 return -1;
}

    return 0;
}

// 노래 멈춤 (버저 비활성화)
int buzzerStopSong(void) {
    char enablePath[PATH_MAX_LEN];
    snprintf(enablePath, sizeof(enablePath), "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);

    int fd = open(enablePath, O_WRONLY);
    if (fd < 0) {
        perror("open enablePath");
        return -1;
    }
    if (write(fd, "0", 1) != 1) {
    	perror("write");
    	close(fd);
    	return -1;
}
    return 0;
}

