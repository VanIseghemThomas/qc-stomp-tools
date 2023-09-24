#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>

const uint32_t IOCTL_SET_LED = 0x4004e101;

typedef struct {
    uint8_t led_index;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_rgb_cfg_t;

int main(int argc, char const *argv[])
{
    // Validate arguments
    if(argc-1 != 4) {
        printf("Usage: set_led <led_index> <red> <green> <blue>\n");
        // printf("Usage: set_led <led-index> <color>\n");
        return 1;
    }

    // Open the file descriptor
    int fd = open("/dev/zencoderfd", O_RDWR);
    if (fd == -1) {
        // Handle error
        printf("Error while reading file descriptor\n");
        return 1;
    }

    led_rgb_cfg_t conf;

    // Parse the arguments to the struct
    conf.led_index = atoi(argv[1]);
    conf.red = atoi(argv[2]);
    conf.green = atoi(argv[3]);
    conf.blue = atoi(argv[4]);

    printf("lednbr: %d\n", conf.led_index);
    printf("red: %d\n", conf.red);
    printf("green: %d\n", conf.green);
    printf("blue: %d\n", conf.blue);

    printf("Calling ioctl\n");
    if (ioctl(fd, IOCTL_SET_LED, &conf) == -1) {
        printf("Error calling ioctl\n");
    }

    return 0;
}
