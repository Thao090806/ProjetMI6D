#ifndef INIT_H
#define INIT_H

#include "../include/characters.h"

Fighters init_fighter(char *nom, char *description, int pv_max, int attaque, int defense, int agilite, int vitesse) {
    Fighters fighter;

    strcpy(fighter.nom, nom);
    strcpy(fighter.description, description);
    fighter.pv_max = pv_max;
    fighter.pv_courant = pv_max;
    fighter.attaque = attaque;
    fighter.defense = defense;
    fighter.agilite = agilite;
    fighter.vitesse = vitesse;
    fighter.nb_skills = 0;
    fighter.nb_effects = 0;

    return fighter;
}

Skills init_skill(char *nom, char *description, int coefficient, int tours_actifs, int tours_recharge) {
    Skills skill;

    strcpy(skill.nom, nom);
    strcpy(skill.description, description);
    skill.coefficient = coefficient; 
    skill.tours_actifs = tours_actifs; 
    skill.tours_recharge = tours_recharge; 

    return skill;
}


#endif