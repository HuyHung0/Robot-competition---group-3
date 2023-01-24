# Makefile for cross compiling. Create .o file in docker using arm-linux-gnueabi-gcc
# Copy the object file to the robot, the compiling with gcc in the robot
# gcc tester.o -Wall -lm -lev3dev-c -o tester
# gcc i2c.o -Wall -lm -lev3dev-c -o i2c
# gcc tester.o -Wall -lm -lev3dev-c -o tester
# ./i2c
# ./tester
# CC = arm-linux-gnueabi-gcc
CC = gcc
FILE = *.c
FILE_TO_DELETE = *.o

tacho: tacho.c
	rm -f tacho.o
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c tacho.c -o tacho.o
	$(CC) tacho.o -Wall -lm -lev3dev-c -o tacho
sensor: sensor.c
	rm -f sensor.o
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c sensor.c -o sensor.o
	$(CC) sensor.o -Wall -lm -lev3dev-c -o sensor
tester: tester.c
	rm -f tester.o
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c tester.c -o tester.o
	$(CC) tester.o -Wall -lm -lev3dev-c -o tester
go_straight: go_straight.c
	rm -f go_straight.o
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c go_straight.c -o go_straight.o
	$(CC) go_straight.o -Wall -lm -lev3dev-c -o go_straight
go_straightV2: go_straightV2.c
	rm -f go_straightV2.o
	$(CC) -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c go_straightV2.c -o go_straightV2.o
	$(CC) go_straightV2.o -Wall -lm -lev3dev-c -o go_straightV2
clean:
	rm -f $(FILE_TO_DELETE)
