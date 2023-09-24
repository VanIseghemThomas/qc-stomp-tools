CC=$(CROSS_COMPILE)gcc
CFLAGS=-g -Wall -static

OUTPUT=set_led

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) set_led.c
	
clean: 
	rm -rf $(OUTPUT)

native:
	gcc $(CFLAGS) -o $(OUTPUT) set_led.c