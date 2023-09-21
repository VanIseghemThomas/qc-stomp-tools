CC=$(CROSS_COMPILE)gcc
CFLAGS=-g -Wall -static

OUTPUT=stomp_listener

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) stomp_listener.c stomp.c
	
clean: 
	rm -rf $(OUTPUT)

native:
	gcc $(CFLAGS) -o $(OUTPUT) stomp_listener.c stomp.c