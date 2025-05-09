#ifndef LOGIQUE_H
#define LOGIQUE_H

#include "../entetes/parametres.h"

// Fonctions utilitaires
void attendre(int secondes);
void nettoyer();

// Fonctions d'affichage
int afficher_personnages(Personnage personnages[], int nb_personnages);
void afficher_equipe(Equipe equipe_joueur[], Equipe equipe_ennemi[]);

// Gestion des équipes
int choisir_personnage(int nb_personnages);
void choisir_equipe(Personnage personnages[], int nb_personnages, Equipe equipe[]);
void equipe_aleatoire(Personnage personnages[], int nb_personnages, Equipe equipe[]);

// Modes de jeu
void mode_univers(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[]);
void mode_versus(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[]);
void mode_aleatoire(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[]);

// Fonction principale
void charger(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[], int mode);

#endif