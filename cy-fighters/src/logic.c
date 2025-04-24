#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "../data/init.h"

/*
    Inclusion indirecte de characters.h.
    characters.h : contient la structure des personnages leurs compétences et les equipes.
 */

 #define MAX_FIGHTERS 6 // Nombre maximum de personnages

void init_fighters(Fighters fighters[]) {
    /*
        Initialisation des personnages avec leurs caractéristiques respectives.
        Chaque personnage a un nom, 
        des points de vie max (0 à 10), 
        une attaque, 
        une défense, 
        une agilité et 
        une vitesse.
    */
    fighters[0] = init_fighter("Chevalier", "Guerrier equilibre", 100, 70, 80, 40, 30);
    fighters[1] = init_fighter("Bandit", "Agile mais fragile", 70, 60, 40, 70, 50);
    fighters[2] = init_fighter("Sorcier", "Puissant mais fragile", 50, 90, 20, 60, 40); 
    fighters[3] = init_fighter("Epeiste", "Combattant equilibre", 80, 80, 60, 80, 45);
    fighters[4] = init_fighter("Archer", "Rapide et precis", 60, 70, 30, 90, 60);
    fighters[5] = init_fighter("Assassin", "Rapide et offensif", 50, 90, 20, 100, 70);
}


int show_fighters(Fighters fighters[], int nb_fighters) {
    /*
        Affiche les personnages disponibles pour le joueur.
        Renvoie le nombre de personnages disponibles.
    */
    printf("Personnages disponibles :\n");
    for (int i = 0; i < nb_fighters; i++) {
        printf("> %s - %s\n", fighters[i].nom, fighters[i].description);
        printf("  Statistique :\n");
        printf("  - Point de vie : %d/100\n", fighters[i].pv_courant, fighters[i].pv_max);
        printf("  - Attaque : %d/100\n", fighters[i].attaque);
        printf("  - Defense : %d/100\n", fighters[i].defense);
        printf("  - Agilite : %d/100\n", fighters[i].agilite);
        printf("  - Vitesse : %d/100\n", fighters[i].vitesse);
        printf("\n");
    }
    return nb_fighters;
}

int select_fighter(Fighters fighters[], int nb_fighters) {
    /*
    Sélectionne un personnage parmi les personnages disponibles.
    Renvoie l'index du personnage sélectionné.
    */
    int choix = -1; // Initialisation de choix à une valeur invalide

    while (1) { // Boucle infinie pour gérer les entrées invalides
        printf("Choisissez votre personnage (0-%d) : ", nb_fighters - 1);
        if (scanf("%d", &choix) == 1 && choix >= 0 && choix < nb_fighters) {
            // Si l'entrée est valide, on sort de la boucle
            break;
        } else {
            // Si l'entrée est invalide, afficher un message d'erreur
            printf("Choix invalide. Veuillez entrer un nombre entre 0 et %d.\n", nb_fighters - 1);
            while (getchar() != '\n'); // Nettoyer le buffer d'entrée
        }
    }

    printf("Vous avez choisi %s !\n", fighters[choix].nom);
    return choix; // Retourne l'index du personnage sélectionné
}
    
void game() {
    /*
        Fonction principale du jeu.
        Initialise les personnages et l'équipe, 
        affiche les personnages disponibles, 
        et permet au joueur de sélectionner un personnage.
    */
    Fighters fighters[MAX_FIGHTERS]; // Allocation d'un tableau de personnages
    init_fighters(fighters); // Initialisation des personnages
    show_fighters(fighters, MAX_FIGHTERS); // Affichage des personnages disponibles
    select_fighter(fighters, MAX_FIGHTERS); // Sélection du personnage par le joueur
}

#endif