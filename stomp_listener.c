#include <stdio.h>
#include <stdlib.h>
#include "stomp.h"

int main()
{
    FILE *files[12];
    
    printf("Starting stomp listener\n");
    OpenFiles(files);

    printf("Listening to stomp messages\n");
    while (1)
    {
        struct StompMessage **messages = ReadStomps(files);
        for (int i = 0; i < N_STOMPS; i++)
        {
            if (messages[i] != NULL)
            {
                printf("============= Stomp %d =============\n", i);
                printf("Action: %d\n", messages[i]->action);
                printf("Value: %u\n", messages[i]->value);
                printf("Timestamp: %u\n", messages[i]->timestamp);
                printf("\n");
                free(messages[i]);
            }
        }
        free(messages);
    }    

    printf("Closing stomp listeners\n");
    CloseFiles(files);

    return 0;
}
