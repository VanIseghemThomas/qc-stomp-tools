#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include "stomp_led.h"

volatile sig_atomic_t stop_flag = 0;

typedef struct {
    int hue;
    int saturation;
    int value;
} hsv;

hsv colors[9];

void sigint_handler(int signum) {
    stop_flag = 1;
    printf("Stopping...\n");
}

void HsvToRgb(int hue, int saturation, int value, int *red, int *green, int *blue) {
    int chroma = (value * saturation) / 255;
    int hue_prime = hue / 60;
    int x = chroma * (255 - abs((hue % 60) - 255)) / 255;
    int m = value - chroma;

    switch (hue_prime) {
        case 0:
            *red = chroma;
            *green = x;
            *blue = 0;
            break;
        case 1:
            *red = x;
            *green = chroma;
            *blue = 0;
            break;
        case 2:
            *red = 0;
            *green = chroma;
            *blue = x;
            break;
        case 3:
            *red = 0;
            *green = x;
            *blue = chroma;
            break;
        case 4:
            *red = x;
            *green = 0;
            *blue = chroma;
            break;
        case 5:
            *red = chroma;
            *green = 0;
            *blue = x;
            break;
        default:
            *red = 0;
            *green = 0;
            *blue = 0;
            break;
    }

    *red += m;
    *green += m;
    *blue += m;
}

void InitColors(int spectrum, int brightness) {
    int hue = 0;
    int offset = spectrum / 9;
    for (int i = 0; i < 9; i++) {
        // Increment hue for next LED
        hue += offset;
        if (hue >= 360) {
            hue = 0;
        }
        colors[i].hue = hue; 
        colors[i].saturation = 255;
        colors[i].value = brightness;      
    }
}

int main(int argc, char const *argv[])
{
    // Validate arguments
    if(argc-1 != 3) {
        printf("Usage: set_led <hue-offset (degrees)> <brightness (0-255)> <spectrum (0-360)>\n");
        return 1;
    }

    int hue_offset = atoi(argv[1]);
    uint8_t brightness = (uint8_t)atoi(argv[2]);
    int spectrum = atoi(argv[3]);

    OpenZencoderFd();

    // Register signal handler for SIGINT
    signal(SIGINT, sigint_handler);
    
    // Initialize the colors for each LED
    InitColors(spectrum, brightness);
    while (!stop_flag) {
        for (int i = 0; i < 9; i++) {
            // Calculate RGB values from hue
            int red, green, blue;
            
            HsvToRgb(colors[i].hue, colors[i].saturation, colors[i].value, &red, &green, &blue);
    
            // Set LED color
            SetLedAtIndexRGB(i, red, green, blue);
            colors[i].hue += hue_offset;
            if(colors[i].hue >= 360){
                colors[i].hue = 0;
            }
        }

        // Wait for a short time before updating LEDs again
        usleep(50000);
    }

    DisableAllLeds();
    CloseZencoderFd();
    return 0;
}
