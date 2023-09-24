CC=$(CROSS_COMPILE)gcc
CFLAGS=-s -Wall -static

OUTPUT_DIR=../../bin
OUTPUT_NAME=set_led

OUTPUT=$(OUTPUT_DIR)/$(OUTPUT_NAME)

FILES=set_led.c stomp_led.c

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(FILES)
	
clean: 
	rm -rf $(OUTPUT)

native:
	gcc $(CFLAGS) -o $(OUTPUT) $(FILES)