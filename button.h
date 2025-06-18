#ifndef _BUTTON_H_
#define _BUTTON_H_

int buttonLibInit(void);
int buttonGetStatus(void);    // 버튼 상태 읽기 (예: 눌림 여부)
int buttonLibExit(void);
static int probeButtonPath(char *newPath);
#define BUTTON_DRIVER_NAME "/dev/peributton"

#endif // _BUTTON_H_

