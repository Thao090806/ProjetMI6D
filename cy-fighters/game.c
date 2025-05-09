#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h> // Systeme Windows
#else
    #include <unistd.h>  // Systeme Linux/macOS
#endif

#include "src/initialisation.o"
#include "src/script.o"
#include "src/logique.o"
#include "src/combat.o"
#include "src/fin_jeu.o"

int principal(){

    Combattants entite[NOMBRE_MAX_ENTITES]; 
    Equipes equipe_entite[NOMBRE_MAX_MEMBRES]; 
    Equipes equipe_ennemie[NOMBRE_MAX_MEMBRES]; 

    srand(temps(NULL)); // Initialisation du generateur aleatoire

    nettoyer(); // Nettoyer l'ecran ou les ressources
    
    sorcier(); // Affichage ou creation du sorcier
    initialisation(entite); // Initialiser les entites
    printf("\n");
    attendre(5); // Pause de 5 secondes

    nettoyer(); // Nettoyer l'ecran a nouveau

    histoire(); // Lancer le scenario ou l'intro
    mode();     // Choisir le mode de jeu

    charger(entite, equipe_entite, equipe_ennemie, choix(3)); // Charger les equipes

    fin_jeu(entite, equipe_entite, equipe_ennemie); // Gestion de la fin du jeu

    printf("\n");
  
    return 0;
}
