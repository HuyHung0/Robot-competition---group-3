# Makefile for compiling an ev3 project with the following folder structure:
#
#	this_folder/
# 		Makefile (this file)
#		ev3dev-c/
#		libraries/
#			libbluetooth.a
#			libev3dev-c.a
#		include/
# 			bt_client.h
#			messages.h
#			movement.h
#			sensors.h
#	 	source/
#			sensors.c
#			
#		bin/
#			sensors
#
# The main executable will be located in the same directory as you ran 
# "Make" from. To add new .c files, simply add them to the OBJS variable.

CC 			= arm-linux-gnueabi-gcc
CFLAGS 		= -O2 -g -std=gnu99 -W -Wall -Wno-comment
INCLUDES 	= -I./ev3dev-c/source/ev3 -I./include/
LDFLAGS 	= -L./libraries -lm -lev3dev-c
BUILD_DIR 	= ./build
SOURCE_DIR 	= ./source
BIN_DIR		= ./bin

SRCS = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
EXECS = $(SRCS:$(SOURCE_DIR)/%.c=$(BIN_DIR)/%)

all: $(EXECS)

$(EXECS): $(BIN_DIR)/%: $(BUILD_DIR)/%.o
	$(CC) $(INCLUDES) $(CFLAGS) $< $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c $< $(INCLUDES) -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir $@

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(EXECS)

