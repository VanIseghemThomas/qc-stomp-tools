CC=$(CROSS_COMPILE)gcc
CFLAGS=-g -Wall -static

OUTPUT=stomp_listener

all: stomp_listener.c
	$(CC) $(CFLAGS) -o $(OUTPUT) stomp_listener.c
	
clean: 
	rm -rf $(OUTPUT)