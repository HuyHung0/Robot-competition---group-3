# Makefile for cross compiling. Create .o file in docker using arm-linux-gnueabi-gcc
# Copy the object file to the robot, the compiling with gcc in the robot
# gcc tester.o -Wall -lm -lev3dev-c -o tester
# gcc i2c.o -Wall -lm -lev3dev-c -o i2c
# gcc tester.o -Wall -lm -lev3dev-c -o tester
# ./i2c
# ./tester
CC = arm-linux-gnueabi-gcc

all:
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c tester.c -o tester.o
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c i2c.c -o i2c.o
i2c:
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c i2c.c -o i2c.o
tester:
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c tester.c -o tester.o


