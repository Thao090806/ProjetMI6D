#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "src\logic.c" 
/*
    Inclusion indirecte de characters.h et init.h.
    characters.h : contient la structure des personnages leurs compétences et les equipes.
    init.h : contient la fonction d'initialisation des personnages et de l'équipe.
 */

int main(){

    game(); // Appel de la fonction principale du jeu
  
    return 0;
}