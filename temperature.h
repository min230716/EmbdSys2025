#ifndef TEMPERATURE_H
#define TEMPERATURE_H

char gbuf[10];

int spi_init(char filename[40]);
char *spi_read_lm74(int file);

#endif
