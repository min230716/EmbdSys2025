#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "temperature.h"

int spi_initc(const char *filename) {
    int file;
    __u8 mode = 0, lsb, bits;
    __u32 speed = 20000;

    if ((file = open(filename, O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        printf("ErrorType:%d\r\n", errno);
        exit(1);
    }

    mode |= SPI_3WIRE;

    if (ioctl(file, SPI_IOC_RD_MODE, &mode) < 0) {
        perror("SPI rd_mode");
        return 0;
    }
    if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
        perror("SPI rd_lsb_first");
        return 0;
    }
    if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("SPI bits_per_word");
        return 0;
    }

    printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",
           filename, mode, bits, lsb ? "(lsb first) " : "", speed);
    return file;
}


char *spi_read_lm74(int file) {
    int len;
    memset(gbuf, 0, sizeof(gbuf));
    len = read(file, gbuf, 2);
    if (len !=2) {
        perror("read error");
        return NULL;
    }
    return gbuf;
}
