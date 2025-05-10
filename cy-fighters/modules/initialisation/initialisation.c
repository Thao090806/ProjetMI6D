#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Personnage creer_personnage(char *nom, char *description, int pv_max, int attaque, int defense, int agilite, int vitesse) {
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

    return personnage;
}

Competence creer_competence(char *nom, char *description, int coefficient, int tours_actifs, int tours_recharge) {
    Competence competence;

    strcpy(competence.nom, nom);
    strcpy(competence.description, description);
    competence.coefficient = coefficient;
    competence.tours_actifs = tours_actifs;
    competence.tours_recharge = tours_recharge;

    return competence;
}

void charger_personnages(Personnage personnages[]) {
    char source[MAX_CARACTERES] = "donnees/personnages.txt";
    printf("Chargement des personnages depuis %s...\n", source);

    FILE *fp = fopen(source, "r");
    if (fp == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", source);
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
    char source[MAX_CARACTERES] = "donnees/competences.txt";
    printf("Chargement des competences depuis %s...\n", source);

    FILE *fp = fopen(source, "r");
    if (fp == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", source);
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
                personnages[index].nb_competences++;
            }
            index++;
        }
    }

    fclose(fp);
    printf("Chargement des competences termine.\n");
}

void initialiser(Personnage entites[]) {
    charger_personnages(entites);
    charger_competences(entites);
}

