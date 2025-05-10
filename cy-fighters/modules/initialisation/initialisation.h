#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "../../entetes/parametres.h"


Personnage creer_personnage(char *nom, char *description, int pv_max, int attaque, int defense, int agilite, int vitesse);
Competence creer_competence(char *nom, char *description, int coefficient, int tours_actifs, int tours_recharge);
void charger_personnages(Personnage personnages[]);
void charger_competences(Personnage personnages[]);
void initialiser(Personnage entites[]);

#endif