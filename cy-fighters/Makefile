all: exec

jeu.o: jeu.c jeu.h
    gcc -c jeu.c -o jeu.o

script.o: script.c script.h
    gcc -c script.c -o script.o

logique.o: logique.c logique.h
    gcc -c logique.c -o logique.o

initialisation.o: initialisation.c initialisation.h
    gcc -c initialisation.c -o initialisation.o

combat.o: combat.c combat.h
    gcc -c combat.c -o combat.o

finjeu.o: finjeu.c finjeu.h
    gcc -c finjeu.c -o finjeu.o

exec: jeu.o script.o logique.o initialisation.o combat.o finjeu.o
    gcc -o exec jeu.o script.o logique.o initialisation.o combat.o finjeu.o

clean:
    rm -f *.o
    rm -f exec