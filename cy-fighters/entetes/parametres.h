#ifndef PARAMETRES_H
#define PARAMETRES_H

#define MAX_EQUIPES 2
#define MAX_PERSONNAGES 6
#define MAX_COMPETENCES 3
#define MAX_MEMBRES 3
#define MAX_EFFETS 10
#define MAX_NOM 35
#define MAX_DESCRIPTION 200
#define MAX_FICHIERS 10000
#define MAX_CARACTERES 1000

typedef struct {
    char nom[MAX_NOM];
    char description[MAX_DESCRIPTION];
    int coefficient;
    int tours_actifs;
    int tours_recharge;
} Competence;

typedef struct {
    Competence *competence;
    char nom[MAX_NOM];
    int tours_restants;
    int valeur;
} Effet;

typedef struct {
    char nom[MAX_NOM];
    char description[MAX_DESCRIPTION];
    int pv_max;
    int pv_actuels;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    Competence competences[MAX_COMPETENCES];
    int nb_competences;
    int recharge[MAX_COMPETENCES];
    Effet effets[MAX_EFFETS];
    int nb_effets;
} Personnage;

typedef struct {
    char *nom;
    Personnage membres[MAX_MEMBRES];
    int nb_membres;
} Equipe;

#endifsdsd