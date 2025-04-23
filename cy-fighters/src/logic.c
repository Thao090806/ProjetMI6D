#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__
#include "../data/init.h"

/*
    Inclusion indirecte de characters.h.
    characters.h : contient la structure des personnages leurs compétences et les equipes.
 */

void init(Fighters fighters[]) {
    /*
        Initialisation des personnages avec leurs caractéristiques respectives.
        Chaque personnage a un nom, 
        des points de vie max, 
        une attaque, 
        une défense, 
        une agilité et 
        une vitesse.
    */
    
    fighters[0] = init_fighter("Naruto", 180, 35, 20, 25, 22);
    fighters[1] = init_fighter("Sasuke", 170, 35, 18, 28, 28);
    fighters[2] = init_fighter("Minato", 160, 38, 25, 30, 30);
    fighters[3] = init_fighter("Kakashi", 190, 38, 22, 26,23);
    fighters[4] = init_fighter("Gaara", 200, 30, 35, 15, 12);
    fighters[5] = init_fighter("Itachi", 180, 45, 20, 30, 25);
}

int select_fighter(Fighters fighters[], int nb_fighters) {
    /*
        Sélectionne un personnage parmi les personnages disponibles.
        Affiche la liste des personnages et demande à l'utilisateur de choisir un personnage.
        Renvoie l'index du personnage sélectionné.
    */
    
    printf("Sélectionnez votre personnage :\n");
    for (int i = 0; i < nb_fighters; i++) {
        printf("%d. %s\n", i + 1, fighters[i].nom);
        printf("   PV : %d\n", fighters[i].pv_max);
        printf("   Attaque : %d\n", fighters[i].attaque);
        printf("   Défense : %d\n", fighters[i].defense);
        printf("   Agilité : %d\n", fighters[i].agilite);
        printf("   Vitesse : %d\n", fighters[i].vitesse);
        printf("\n");
    }
    int choix;
    printf("Entrez le numéro de votre choix : ");
    scanf("%d", &choix);
    return choix - 1; // Retourne l'index du personnage sélectionné
}


#endif // __CHARACTERS_H__