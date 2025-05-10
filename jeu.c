#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "entetes/parametres.h"
#include "modules/initialisation/initialisation.h"
#include "modules/script/script.h"
#include "modules/logique/logique.h"
#include "modules/combat/combat.h"
#include "modules/finjeu/finjeu.h"

int main() {
    // Initialisation des structures
    Personnage entites[MAX_PERSONNAGES];
    Equipe equipe_joueur[MAX_MEMBRES];
    Equipe equipe_ennemi[MAX_MEMBRES];

    // Initialisation du générateur aléatoire
    srand(time(NULL));

    // Nettoyer l'écran et afficher l'introduction
    nettoyer();
    afficher_magicien();
    
    // Initialiser les personnages et compétences
    initialiser(entites);
    printf("\n");
    attendre(5);
    nettoyer();

    // Afficher l'histoire et les modes de jeu
    histoire();
    mode_jeu();

    // Charger le mode de jeu sélectionné
    charger(entites, equipe_joueur, equipe_ennemi, demander(2));

    // Fin du jeu
    liberation_de_memoire(entites, equipe_joueur, equipe_ennemi);
    printf("\n");

    return 0;
}