#ifndef INIT_H
#define INIT_H
#include "../include/characters.h"

Fighters init_fighter(char *nom, int pv_max, int attaque, int defense, int agilite, int vitesse) {
    Fighters fighter;
    strcpy(fighter.nom, nom);
    fighter.pv_max = pv_max;
    fighter.pv_courant = pv_max;
    fighter.attaque = attaque;
    fighter.defense = defense;
    fighter.agilite = agilite;
    fighter.vitesse = vitesse;
    fighter.nb_skills = 0;
    fighter.nb_effets = 0;
    return fighter;
}

#endif