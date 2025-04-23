#ifndef CHARACTERS_H  // Vérifie si CHARACTERS_H n'est pas défini
#define CHARACTERS_H  // Définit CHARACTERS_H
#define MAX_SKILLS 3
#define MAX_MEMBRES 3
#define MAX_EFFETS 5

typedef struct {
    char nom[30]; 
    int valeur;
    char description[100];
    int nombre_tours_actifs;
    int cooldown;
} Skills;

typedef struct {
    Skills *skills;
    int tours_restants;
} Effetspecial;

typedef struct {
    char nom[30];
    int pv_max;
    int pv_courant;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    Skills skills[MAX_SKILLS];
    int nb_skills;
    Effetspecial effet[MAX_EFFETS];
    int nb_effets;
} Fighters;

typedef struct {
    char *nom;
    Fighters fighters[MAX_MEMBRES];
    int nb_membres;
} Teams;

#endif  // Fin de la garde d'inclusion