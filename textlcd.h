#ifndef TEXTLCD_H
#define TEXTLCD_H

#include "textlcddrv.h"

#define TEXTLCD_DRIVER_NAME "/dev/peritextlcd"
void TextLCD_write(const char* line1, const char* line2);
void doHelp(void);

#endif
