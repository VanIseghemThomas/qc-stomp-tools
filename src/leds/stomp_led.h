#ifndef STOMP_LED_H
#define STOMP_LED_H

#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    uint8_t led_index;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_rgb_cfg_t;

int OpenZencoderFd();
int CloseZencoderFd();
int SetLedAtIndexRGB(int led_index, int red, int green, int blue);

#endif // STOMP_LED_H
