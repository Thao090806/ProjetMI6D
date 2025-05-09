#ifndef SETTINGS_H 
#define SETTINGS_H  

#define MAX_TEAMS 2
#define MAX_ENTITYS 6
#define MAX_SKILLS 3
#define MAX_MEMBRES 3
#define MAX_EFFETS 10
#define MAX_NAME 35
#define MAX_DESCRIPTION 200
#define MAX_FILES 10000
#define MAX_CARATERES 1000

typedef struct {
    char nom[MAX_NAME];
    char description[MAX_DESCRIPTION];
    int coefficient;
    int tours_actifs;
    int tours_recharge;
} Competence;

typedef struct {
    Skills *skills;
    char nom[MAX_NAME];
    int tours_restants;
    int valeur;
} Effets;

typedef struct {
    char nom[MAX_NAME];
    char description[MAX_DESCRIPTION];
    int pv_max;
    int pv_courant;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    Competence competence [MAX_SKILLS];
    int nb_competence;
    int rechargement[MAX_SKILLS];
    Effets effets[MAX_EFFETS];
    int nb_effets;
} Combattants;

typedef struct {
    char *nom;
    Combattants combattants[MAX_MEMBRES];
    int nb_membres;
} Equipe;

#endif  
