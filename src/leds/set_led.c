#include <stdio.h>
#include <stdlib.h>
#include "stomp_led.h"

int main(int argc, char const *argv[])
{
    // Validate arguments
    if(argc-1 != 4) {
        printf("Usage: set_led <led_index> <red> <green> <blue>\n");
        return 1;
    }

    // Parse arguments
    int led_index = atoi(argv[1]);
    int red = atoi(argv[2]);
    int green = atoi(argv[3]);
    int blue = atoi(argv[4]);
    OpenZencoderFd();
    SetLedAtIndexRGB(led_index, red, green, blue);
    CloseZencoderFd();
    return 1;
}
