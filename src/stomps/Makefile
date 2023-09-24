CC=$(CROSS_COMPILE)gcc
CFLAGS=-s -Wall -static

OUTPUT_DIR=../../bin
OUTPUT_NAME=stomp_listener

OUTPUT=$(OUTPUT_DIR)/$(OUTPUT_NAME)

FILES=stomp_listener.c stomp.c

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(FILES)
	
clean: 
	rm -rf $(OUTPUT)

native:
	gcc $(CFLAGS) -o $(OUTPUT) $(FILES)