CC=$(CROSS_COMPILE)gcc
CFLAGS=-s -Wall -static

OUTPUT_DIR=../../bin

all:
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/set_led stomp_led.c set_led.c
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/led_rainbow stomp_led.c rainbow.c
	
clean: 
	rm -rf $(OUTPUT)

native:
	gcc $(CFLAGS) -o $(OUTPUT_DIR)/set_led stomp_led.c set_led.c
	gcc $(CFLAGS) -o $(OUTPUT_DIR)/led_rainbow stomp_led.c rainbow.c