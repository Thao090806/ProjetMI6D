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
    initialisation.h : contient la fonction d'initialisation des personnages et de l'équipe.
    logic.c : contient la logique du jeu, les fonctions de combat et de gestion des personnages.
 */

int main(){

    game(); // Appel de la fonction principale du jeu
  
    return 0;
}