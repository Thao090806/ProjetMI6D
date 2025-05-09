#ifndef PARAMETRES_H
#define PARAMETRES_H

// Constantes de configuration
#define MAX_EQUIPES 2
#define MAX_ENTITES 6
#define MAX_CAPACITES 3
#define MAX_MEMBRES 3
#define MAX_EFFETS 10
#define MAX_NOM 35
#define MAX_DESCRIPTION 200
#define MAX_FICHIERS 10000
#define MAX_CARACTERES 1000

// Structure pour les capacités des personnages
typedef struct {
    char nom[MAX_NOM];
    char description[MAX_DESCRIPTION];
    int coefficient;       // Multiplicateur de dégâts
    int tours_actifs;      // Durée de l'effet
    int tours_recharge;    // Temps de recharge
} Capacite;

// Structure pour les effets actifs
typedef struct {
    Capacite *capacites;   // Capacité liée à l'effet
    char nom[MAX_NOM];     // Nom de l'effet
    int tours_restants;    // Durée restante
    int valeur;            // Valeur de l'effet
} Effet;

// Structure principale des personnages
typedef struct {
    char nom[MAX_NOM];
    char description[MAX_DESCRIPTION];
    int pv_max;            // Points de vie maximum
    int pv_actuels;        // Points de vie actuels
    int attaque;           // Force d'attaque
    int defense;           // Résistance aux dégâts  
    int agilite;           // Chance d'esquiver
    int vitesse;           // Ordre d'attaque
    
    Capacite capacites[MAX_CAPACITES];  // Liste des capacités
    int nb_capacites;                   // Nombre de capacités
    
    int rechargement[MAX_CAPACITES];    // Temps de recharge restant
    
    Effet effets[MAX_EFFETS];           // Effets actifs
    int nb_effets;                      // Nombre d'effets
} Personnage;

// Structure pour les équipes
typedef struct {
    char *nom;                          // Nom de l'équipe
    Personnage membres[MAX_MEMBRES];    // Membres de l'équipe
    int nb_membres;                     // Nombre de membres
} Equipe;

#endif