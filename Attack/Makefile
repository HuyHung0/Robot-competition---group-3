all:
        gcc -std=gnu99 -W -Wall -pthread -c attackmain.c -o attackmain.o
        gcc -std=gnu99 -W -Wall -pthread -c attacker.c -o attacker.o
        gcc attacker.o attackmain.o -Wall -pthread -lm -lev3dev-c -pthread -o AttackMode


attack:
         gcc -std=gnu99 -W -Wall -pthread -c attacker.c -o attacker.o


attackmain:
          gcc -std=gnu99 -W -Wall -pthread -c attackmain.c -o attackmain.o


clean:
        rm attacker.o attackmain.o AttackMode