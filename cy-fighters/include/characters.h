#ifndef CHARACTERS_H 
#define CHARACTERS_H  

#define MAX_FIGHTERS 6
#define MAX_SKILLS 3
#define MAX_MEMBRES 3
#define MAX_EFFETS 5

typedef struct {
    char nom[35];
    char description[150];
    int coefficient;
    int tours_actifs;
    int tours_recharge;
} Skills;

typedef struct {
    Skills *skills;
    int tours_restants;
} Effects;

typedef struct {
    char nom[35];
    char description[150];
    int pv_max;
    int pv_courant;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    Skills skills[MAX_SKILLS];
    int nb_skills;
    Effects effects[MAX_EFFETS];
    int nb_effects;
} Fighters;

typedef struct {
    char *nom;
    Fighters fighters[MAX_MEMBRES];
    int nb_membres;
} Teams;

#endif  