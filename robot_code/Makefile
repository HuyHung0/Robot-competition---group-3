# Makefile for cross-compiling c file on docker for the robot ev3 with the following folder structure:
#
#	this_folder/
# 		Makefile (this file)
#		ev3dev-c/
#		libraries/
#			libev3dev-c.a
#		include/
#			//file .h
#	 	source/
#			file .c		
#		bin/
#			binary file generated
#
# The make command will compile all present c file in folder source/
# and generated the corresponding binary file (with corresponding name) in folder bin/


CC 			= arm-linux-gnueabi-gcc
CFLAGS 		= -O2 -g -std=gnu99 -W -Wall -Wno-comment
INCLUDES 	= -I./ev3dev-c/source/ev3 -I./include/
LDFLAGS 	= -L./libraries -lm -lev3dev-c -pthread
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

