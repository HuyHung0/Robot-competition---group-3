all:
	gcc -std=gnu99 -W -Wall -pthread -c defendermain.c -o defendermain.o
	gcc -std=gnu99 -W -Wall -pthread -c defender.c -o defender.o
	gcc defender.o defendermain.o -Wall -pthread -lm -lev3dev-c -pthread -o DefenceMode

clean:
	rm defender.o defendermain.o DefenceMode
