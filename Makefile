# Cible par défaut
all: exec

# Compilation des fichiers objets
jeu.o: jeu.c
	gcc -c jeu.c -o jeu.o

modules/script/script.o: modules/script/script.c modules/script/script.h
	gcc -c modules/script/script.c -o modules/script/script.o

modules/logique/logique.o: modules/logique/logique.c modules/logique/logique.h
	gcc -c modules/logique/logique.c -o modules/logique/logique.o

modules/initialisation/initialisation.o: modules/initialisation/initialisation.c modules/initialisation/initialisation.h
	gcc -c modules/initialisation/initialisation.c -o modules/initialisation/initialisation.o

modules/combat/combat.o: modules/combat/combat.c modules/combat/combat.h
	gcc -c modules/combat/combat.c -o modules/combat/combat.o

modules/finjeu/finjeu.o: modules/finjeu/finjeu.c modules/finjeu/finjeu.h
	gcc -c modules/finjeu/finjeu.c -o modules/finjeu/finjeu.o

# Lien des fichiers objets pour créer l'exécutable
exec: jeu.o modules/script/script.o modules/logique/logique.o modules/initialisation/initialisation.o modules/combat/combat.o modules/finjeu/finjeu.o
	gcc -o exec jeu.o modules/script/script.o modules/logique/logique.o modules/initialisation/initialisation.o modules/combat/combat.o modules/finjeu/finjeu.o

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f jeu.o
	rm -f modules/script/script.o
	rm -f modules/logique/logique.o
	rm -f modules/initialisation/initialisation.o
	rm -f modules/combat/combat.o
	rm -f modules/finjeu/finjeu.o
	rm -f exec
