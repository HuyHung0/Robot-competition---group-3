CC = arm-linux-gnueabi-gcc
INCLUDES = -I./ev3dev-c/source/ev3
CFLAGS = -O2 -std=gnu99 -W -Wall -Wno-comment
BUILD_DIR = ./build
SOURCE_DIR 	= ./source

OBJS = \
	$(BUILD_DIR)/common.o \
	$(BUILD_DIR)/testColor.o \
	$(BUILD_DIR)/testRunning.o \

all: $(OBJS)

$(OBJS): $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $(SOURCE_DIR)/$*.c -o $(BUILD_DIR)/$*.o

clean:
	rm -f $(BUILD_DIR)/*.o