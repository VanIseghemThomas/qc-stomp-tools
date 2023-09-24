#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

static const uint32_t IOCTL_SET_LED = 0x4004e101;
int zencoderfd;

typedef struct {
    uint8_t led_index;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_rgb_cfg_t;

// Open the file descriptor for the Zencoder
int OpenZencoderFd() {
    zencoderfd = open("/dev/zencoderfd", O_RDWR);
    if (zencoderfd == -1) {
        printf("Error while reading file descriptor\n");
        return -1;
    }
    return zencoderfd;
}

// Close the file descriptor for the Zencoder
int CloseZencoderFd() {
    if (close(zencoderfd) == -1) {
        printf("Error while closing file descriptor\n");
        return -1;
    }
    return 0;
}

// Set the color of the LED at the given index
int SetLedAtIndexRGB(int led_index, int red, int green, int blue) {
    if(zencoderfd == -1) {
        printf("Error: file descriptor not open\n");
        return -1;
    }

    led_rgb_cfg_t conf;
    conf.led_index = led_index;
    conf.red = red;
    conf.green = green;
    conf.blue = blue;
    if (ioctl(zencoderfd, IOCTL_SET_LED, &conf) == -1) {
        printf("Error while setting LED, did you open the file descriptor?\n");
        return -1;
    }
    
    printf(
        "[LED set] index: %d, r: %d, g: %d, b: %d\n",
        conf.led_index,
        conf.red,
        conf.green,
        conf.blue
    );

    return 0;
}

void DisableAllLeds(){
    for (int i = 0; i < 11; i++)
    {
        // Ignore the tempo led
        if(i == 9){
            continue;
        }
        SetLedAtIndexRGB(i, 0, 0, 0);
    }
}