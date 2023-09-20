#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const int N_STOMPS = 12;

enum Action
{
    Button = 0,
    Rotary = 1,
};

struct StompMessage{
    unsigned char bytes[32];
    enum Action action;
    unsigned int value;
    unsigned int timestamp;
};

enum KnobValue
{
    Released = 0,
    Pressed = 1,
    TurnedRight = 2,
    TurnedLeft = 3,
};

enum Action DecodeAction(unsigned char bytes[32]){
    if(bytes[10] == 0x11 && bytes[11] == 0x01){
        return Button;
    }
    else if(bytes[10] == 0x08 && bytes[11] == 0x00){
        return Rotary;
    }
    else{
        return -1;
    }
}

enum KnobValue DecodeValue (unsigned char bytes[32]){
    char valueByte = bytes[12];
    if(valueByte == 0x00){
        return Released;
    }
    else if(valueByte == 0x01){
        if(DecodeAction(bytes) == Rotary){
            return TurnedRight;
        }
        else if(DecodeAction(bytes) == Button){
            return Pressed;
        }
        else{
            return -1;
        }
    }
    else if(valueByte == 0xff){
        return TurnedLeft;
    }
    else{
        return -1;
    }
}

// The timestamp is stored in the first 4 bytes of the message (little endian)
unsigned int DecodeTimestamp(unsigned char bytes[32]) {
    unsigned int timestamp = *((unsigned int *)bytes);
    return timestamp;
}

char* ToHexString(unsigned char bytes[]){
    // ?? Not sure why I have to multiply by 4 here
    // Still too new to C to understand probably
    unsigned int amountOfBytes = sizeof(bytes) * 4;
    char* hexString = malloc((amountOfBytes * 3 + 1) * sizeof(char));
    if (hexString == NULL) {
        return NULL;
    }
    for (int i = 0; i < amountOfBytes; i++)
    {
        sprintf(&hexString[i*3], "%02X ", bytes[i]);
    }
    hexString[amountOfBytes*3] = '\0';
    return hexString;
}

void OpenFiles(int fds[12]) {
    for (int i = 1; i < N_STOMPS; i++) {
        char filename[32];
        sprintf(filename, "/dev/zencoder/knob_stomp%d", i);
        printf("\nTrying to open %s", filename);
        // First check if file exists
        int fd = open(filename, O_RDONLY | O_NONBLOCK);
        if (fd == -1) {
            printf("\t[!] File %s does not exist", filename);
        } else {
            printf("\t[+] File %s opened", filename);
            fds[i] = fd;
        }
    }
    printf("\n");
}

void CloseFiles(FILE *files[12]){
    for (int i = 1; i < N_STOMPS; i++)
    {
        if(files[i] == NULL){
            continue;
        }
        fclose(files[i]);
    }
}

void ProcessFile(int *file){
    if(file == -1){
        return;
    }
    
    unsigned char buffer[32];
    ssize_t bytesRead = read(file, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        // Handle error (e.g., EAGAIN/EWOULDBLOCK means no data available)
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return; // No data available, move to the next file
        } else {
            perror("read error");
            // Handle other read errors here
        }
    } else if (bytesRead == 0) {
        // End of file reached, you can handle it as needed
        printf("End of file reached for file %d");
        close(file);
        file = -1;
    } else {
        char* hexString = ToHexString(buffer);
        printf("%s\n", hexString);

        enum Action action = DecodeAction(buffer);
        enum KnobValue value = DecodeValue(buffer);
        unsigned int timestamp = DecodeTimestamp(buffer);

        struct StompMessage stompMessage = {
            .bytes = *buffer,
            .action = action,
            .value = value,
            .timestamp = timestamp,
        };
        
        printf("Bytes: %d\n", (int)sizeof(stompMessage.bytes));
        printf("Action: %d\n", stompMessage.action);
        printf("Value: %u\n", stompMessage.value);
        printf("Timestamp: %u\n", stompMessage.timestamp);
        printf("\n");
    }
}

int main()
{
    FILE *files[12];
    

    printf("Starting stomp listener\n");
    OpenFiles(files);

    printf("Listening to stomp messages\n");
    while (1)
    {
        // Loop over all files and open a filestream
        for (int i = 1; i < 12; i++)
        {
            ProcessFile(files[i]);
        }
    }    

    printf("Closing stomp listeners\n");
    CloseFiles(files);

    return 0;
}
