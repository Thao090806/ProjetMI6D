#ifndef COMBAT_H
#define COMBAT_H

#include "../entetes/parametres.h"

// Fonctions de base
int demander(int max);
int choisir_competence(Personnage *personnage, int index_personnage);
void attaquer_cible(Personnage *attaquant, Personnage *cible, int index_competence, int degats);
void appliquer_effet(Personnage *cible, const char *nom_effet, int valeur, int tours);
void mettre_a_jour_effets(Personnage *cible);
void mettre_a_jour_recharge(Personnage *personnage);

// Fonctions de combat
void effet_cible(Personnage *attaquant, Personnage *cible, int index_competence);
void trier_vitesse(Personnage personnages[], int taille);
void tour_equipe(Equipe *equipe, Personnage *attaquant, Personnage equipe_ennemie[], int nb_ennemis);

// Modes de jeu
void joueur_vs_univers(Equipe *equipe_joueur, Personnage *equipe_j, int nb_joueurs, 
                      Personnage *equipe_ennemie, int nb_ennemis);
void joueur_vs_joueur(Equipe *equipe1, Personnage *equipe_j1, int nb_joueurs1,
                     Equipe *equipe2, Personnage *equipe_j2, int nb_joueurs2);
void robot_vs_robot(Equipe *equipe1, Personnage *robots1, int nb_robots1,
                   Equipe *equipe2, Personnage *robots2, int nb_robots2);

#endif