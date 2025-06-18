CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar
CFLAGS = -Wall -O2 -Wno-unused-result -I../fnd/drv -I../textlcd/drv
LDFLAGS = -static
SRCS = button.c buzzer.c colorled.c \
       fnd.c led.c temperature.c \
       textlcd.c accelMagGyro.c

OBJS = $(SRCS:.c=.o)
TARGET = libembedded.a

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
