CC=$(CROSS_COMPILE)gcc

BUILD_DIR=build
OUTPUT_DIR=bin
INCLUDE_DIR=include
SRC_DIR=src

CFLAGS=-s -Wall -static -std=c99 -I$(INCLUDE_DIR)

# Define the objects to be built for each executable
SET_LED_OBJS=$(BUILD_DIR)/stomp_led.o $(BUILD_DIR)/set_led.o
LED_RAINBOW_OBJS=$(BUILD_DIR)/stomp_led.o $(BUILD_DIR)/rainbow.o
STOMP_LISTENER_OBJS=$(BUILD_DIR)/stomp.o $(BUILD_DIR)/stomp_listener.o

all: $(OUTPUT_DIR)/set_led $(OUTPUT_DIR)/rainbow $(OUTPUT_DIR)/stomp_listener

$(OUTPUT_DIR)/set_led: $(SET_LED_OBJS)
	@echo [Linking $@]
	$(CC) $(CFLAGS) $(SET_LED_OBJS) -o $(OUTPUT_DIR)/set_led

$(OUTPUT_DIR)/rainbow: $(LED_RAINBOW_OBJS)
	@echo [Linking $@]
	$(CC) $(CFLAGS) $(LED_RAINBOW_OBJS) -o $(OUTPUT_DIR)/rainbow

$(OUTPUT_DIR)/stomp_listener: $(STOMP_LISTENER_OBJS)
	@echo [Linking $@]
	$(CC) $(CFLAGS) $(STOMP_LISTENER_OBJS) -o $(OUTPUT_DIR)/stomp_listener

$(BUILD_DIR)/%.o: $(SRC_DIR)/leds/%.c
	@echo [Compiling $<]
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/stomps/%.c
	@echo [Compiling $<]
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: 
	rm -rf $(OUTPUT_DIR)/*
	rm -rf $(BUILD_DIR)/*