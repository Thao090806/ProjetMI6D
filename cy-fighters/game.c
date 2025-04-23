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

#define MAX_FIGHTERS 6 // Nombre maximum de personnages

int main(){
    printf("Bienvenue dans Cy-Fighters !\n");
    printf("Le jeu commence !\n");

    Fighters fighters[MAX_FIGHTERS]; // Tableau de personnages
    init(fighters);
    int choix = select_fighter(fighters, MAX_FIGHTERS);
    printf("Vous avez choisi : %s\n", fighters[choix].nom);
  
    return 0;
}