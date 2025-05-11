#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Personnage creer_personnage(char *nom, char *description, int pv_max, int attaque, int defense, int agilite, int vitesse) {
    /*
    La fonction creer_personnage() crée un personnage avec les paramètres fournis.
    Elle prend en paramètre le nom, la description, les points de vie, l’attaque, la défense, l’agilité et la vitesse du personnage.
    Elle vérifie la validité des paramètres, initialise les champs du personnage, met les compétences en disponible, puis retourne le personnage créé.
    */
    if(nom == NULL || description == NULL || pv_max <= 0 || attaque < 0 || defense < 0 || agilite < 0 || vitesse < 0) {
        fprintf(stderr, "Erreur : Parametres invalides pour le personnage.\n");
        exit(1);
    }
    Personnage personnage;

    strcpy(personnage.nom, nom);
    strcpy(personnage.description, description);
    personnage.pv_max = pv_max;
    personnage.pv_actuels = pv_max;
    personnage.attaque = attaque;
    personnage.defense = defense;
    personnage.agilite = agilite;
    personnage.vitesse = vitesse;
    personnage.nb_competences = 0;
    personnage.nb_effets = 0;

    for (int i = 0; i < MAX_COMPETENCES; i++) {
        personnage.recharge[i] = 0;  // Toutes compétences disponibles au départ
    }

    return personnage;
}

Competence creer_competence(char *nom, char *description, int coefficient, int tours_actifs, int tours_recharge) {
    /*
    La fonction creer_competence() crée une compétence avec les paramètres fournis.
    Elle prend en paramètre le nom, la description, le coefficient, le nombre de tours actifs et le nombre de tours de recharge.
    Elle vérifie la validité des paramètres, initialise les champs de la compétence, puis retourne la compétence créée.
    */
    if(nom == NULL || description == NULL || coefficient < 0 || tours_actifs < 0 || tours_recharge < 0) {
        fprintf(stderr, "Erreur : Parametres invalides pour la competence.\n");
        exit(1);
    }
    Competence competence;

    strcpy(competence.nom, nom);
    strcpy(competence.description, description);
    competence.coefficient = coefficient;
    competence.tours_actifs = tours_actifs;
    competence.tours_recharge = tours_recharge;

    return competence;
}

void charger_personnages(Personnage personnages[]) {
    /*
    La fonction charger_personnages() charge les personnages depuis un fichier texte.
    Elle prend en paramètre un tableau de Personnage.
    Elle ouvre le fichier, lit chaque bloc de personnage, extrait les informations, crée les personnages et les ajoute au tableau.
    */
    if(personnages == NULL) {
        fprintf(stderr, "Erreur : Tableau de personnages null.\n");
        exit(1);
    }
    char source[MAX_CARACTERES] = "donnees/personnages.txt";
    printf("Chargement des personnages depuis %s...\n", source);

    FILE *fp = fopen(source, "r");
    if (fp == NULL) {
        fprintf(stderr, "Erreur : Ouverture du fichier %s compromise.\n", source);
        exit(2);
    }

    char ligne[MAX_FICHIERS];
    int index = 0;

    while (fgets(ligne, MAX_FICHIERS, fp)) {
        if (strncmp(ligne, "Nom;", 4) == 0) {
            char nom[MAX_CARACTERES] = {0};
            char description[MAX_CARACTERES] = {0};
            int pv_max = 0, attaque = 0, defense = 0, agilite = 0, vitesse = 0;

            if (sscanf(ligne, "Nom; %[^\n]", nom) != 1) {
                printf("Erreur : Ligne 'Nom;' mal formatee.\nLigne lue : %s", ligne);
                break;
            }
            
            if (fgets(ligne, MAX_FICHIERS, fp) == NULL || sscanf(ligne, "Description; %[^\n]", description) != 1) {
                printf("Erreur : Ligne 'Description;' mal formee.\nLigne lue : %s", ligne);
                break;
            }
            
            if (fgets(ligne, MAX_FICHIERS, fp) == NULL || sscanf(ligne, "Point de vie max; %d", &pv_max) != 1) {
                printf("Erreur : Ligne 'Point de vie max;' mal formee.\nLigne lue : %s", ligne);
                break;
            }
            
            if (fgets(ligne, MAX_FICHIERS, fp) == NULL || sscanf(ligne, "Attaque; %d", &attaque) != 1) {
                printf("Erreur : Ligne 'Attaque;' mal formee.\nLigne lue : %s", ligne);
                break;
            }

            if (fgets(ligne, MAX_FICHIERS, fp) == NULL || sscanf(ligne, "Defense; %d", &defense) != 1) {
                printf("Erreur : Ligne 'Defense;' mal formee.\nLigne lue : %s", ligne);
                break;
            }

            if (fgets(ligne, MAX_FICHIERS, fp) == NULL || sscanf(ligne, "Agilite; %d", &agilite) != 1) {
                printf("Erreur : Ligne 'Agilite;' mal formee.\nLigne lue : %s", ligne);
                break;
            }

            if (fgets(ligne, MAX_FICHIERS, fp) == NULL || sscanf(ligne, "Vitesse; %d", &vitesse) != 1) {
                printf("Erreur : Ligne 'Vitesse;' mal formee.\nLigne lue : %s", ligne);
                break;
            }

            personnages[index] = creer_personnage(nom, description, pv_max, attaque, defense, agilite, vitesse);
            index++;
        }
    }

    fclose(fp);

    if (index == 0) {
        printf("Erreur : Aucun personnage charge.\n");
        exit(1);
    }

    if (index > MAX_PERSONNAGES) {
        printf("Erreur : Trop de personnages (max %d).\n", MAX_PERSONNAGES);
        exit(1);
    }

    printf("Chargement des personnages termine.\n");
}

void charger_competences(Personnage personnages[]) {
    /*
    La fonction charger_competences() charge les compétences des personnages depuis un fichier texte.
    Elle prend en paramètre un tableau de Personnage.
    Elle ouvre le fichier, lit les blocs de compétences pour chaque personnage, extrait les informations, crée les compétences et les ajoute au bon personnage.
    */
    if(personnages == NULL) {
        fprintf(stderr, "Erreur : Tableau de personnages null.\n");
        exit(1);
    }
    char source[MAX_CARACTERES] = "donnees/competences.txt";
    printf("Chargement des competences depuis %s...\n", source);

    FILE *fp = fopen(source, "r");
    if (fp == NULL) {
        fprintf(stderr, "Erreur : Ouverture du fichier %s compromise.\n", source);
        exit(2);
    }

    char ligne[MAX_FICHIERS];
    int index = 0;

    while (fgets(ligne, MAX_FICHIERS, fp)) {
        if (strncmp(ligne, "Personnage;", 11) == 0) {
            if (index >= MAX_PERSONNAGES || personnages[index].nom[0] == '\0') {
                printf("Erreur : Personnage introuvable pour les competences.\n");
                break;
            }

            char nom[MAX_CARACTERES] = {0};
            char description[MAX_CARACTERES] = {0};
            int coefficient = 0, tours_actifs = 0, tours_recharge = 0;

            for (int i = 0; i < MAX_COMPETENCES; i++) {
                if (fgets(ligne, MAX_FICHIERS, fp) == NULL || strlen(ligne) <= 1 || 
                    sscanf(ligne, "+; %[^\n]", nom) != 1) {
                    printf("Erreur : Ligne de competence mal formatee.\n");
                    continue;
                }

                if (fgets(ligne, MAX_FICHIERS, fp) == NULL || 
                    sscanf(ligne, "Description; %[^\n]", description) != 1) {
                    printf("Erreur : Description mal formatee.\n");
                    break;
                }

                if (fgets(ligne, MAX_FICHIERS, fp) == NULL || 
                    sscanf(ligne, "Coefficient; %d", &coefficient) != 1) {
                    printf("Erreur : Coefficient mal formate.\n");
                    break;
                }

                if (fgets(ligne, MAX_FICHIERS, fp) == NULL || 
                    sscanf(ligne, "Tours actifs; %d", &tours_actifs) != 1) {
                    printf("Erreur : Tours actifs mal formates.\n");
                    break;
                }

                if (fgets(ligne, MAX_FICHIERS, fp) == NULL || 
                    sscanf(ligne, "Tours recharge; %d", &tours_recharge) != 1) {
                    printf("Erreur : Tours recharge mal formates.\n");
                    break;
                }

                if (personnages[index].nb_competences >= MAX_COMPETENCES) {
                    printf("Erreur : Trop de competences pour %s.\n", personnages[index].nom);
                    break;
                }

                personnages[index].competences[i] = creer_competence(nom, description, 
                                                                coefficient, tours_actifs, 
                                                                tours_recharge);
                                                                
                personnages[index].recharge[i] = 0;  // Met à 0 car la compétence est disponible au départ

                personnages[index].nb_competences++;  // Incrémente le compteur
                
            }
            index++;
        }
    }

    fclose(fp);
    printf("Chargement des competences termine.\n");
}

void initialiser(Personnage entites[]) {
    /*
    La fonction initialiser() initialise le jeu en chargeant les personnages et les compétences.
    Elle prend en paramètre un tableau de Personnage.
    Elle vérifie si le tableau de personnages est valide, puis appelle les fonctions de chargement des personnages et des compétences.
    */
    if(entites == NULL) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
        exit(1);
    }
    charger_personnages(entites);
    charger_competences(entites);
}

