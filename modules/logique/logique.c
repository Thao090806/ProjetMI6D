#include "logique.h"
#include "../script/script.h"
#include "../combat/combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void attendre(int secondes) {
    #ifdef _WIN32
        Sleep(secondes * 1000);
    #else
        sleep(secondes);
    #endif
}

void nettoyer() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int afficher_personnages(Personnage personnages[], int nb_personnages) {
    if (personnages == NULL) {
        printf("\033[1;31mErreur : tableau de personnages est NULL.\033[0m\n");
        exit(1);
    }
    if (nb_personnages <= 0 || nb_personnages > MAX_PERSONNAGES) {
        printf("\033[1;31mErreur : nombre de personnages invalide.\033[0m\n");
        exit(3);
    }

    printf("\n");
    for (int i = 0; i < nb_personnages; i++) {
        printf("\033[1;37m%d ~ %s\033[0m ", i, personnages[i].nom);
        printf("(PV: \033[1;33m%d/%d\033[0m, ATK: \033[1;33m%d\033[0m, DEF: \033[1;33m%d\033[0m, AGI: \033[1;33m%d\033[0m, VIT: \033[1;33m%d\033[0m)\n",
               personnages[i].pv_actuels, personnages[i].pv_max, 
               personnages[i].attaque, personnages[i].defense, 
               personnages[i].agilite, personnages[i].vitesse);

        printf("  Competences ~");
        if (personnages[i].nb_competences == 0) {
            printf(" (Aucune)");
        } else {
            for (int j = 0; j < personnages[i].nb_competences; j++) {
                if (personnages[i].competences[j].nom && strlen(personnages[i].competences[j].nom) > 0)
                    printf(" (%s)", personnages[i].competences[j].nom);
            }
        }
        printf("\n");
    }

    return nb_personnages;
}
int choisir_personnage(int nb_personnages) {
    return demander(nb_personnages);
}

void choisir_equipe(Personnage personnages[], int nb_personnages, Equipe equipe[]) {
    if (personnages == NULL || equipe == NULL) {
        printf("\033[1;31mErreur : tableau de personnages/equipes est NULL.\033[0m\n");
        exit(1);
    }
    if (nb_personnages <= 0 || nb_personnages > MAX_PERSONNAGES) {
        printf("\033[1;31mErreur : nombre de personnages invalide.\033[0m\n");
        exit(3);
    }
    printf("\033[0m\033[38;5;214m\033[3m\nQuel sera le nom de votre equipe ? \033[0m");

    char tmp[MAX_CARACTERES];
    scanf("%s", tmp);

    int n = strlen(tmp);
    if (n > MAX_CARACTERES) {
        printf("\033[1;31mHmm ... C'est bien trop long.\n\033[0m");
        exit(1);
    }

    (*equipe).nom = malloc(sizeof(char) * (n + 1));
    strcpy((*equipe).nom, tmp);

    while (getchar() != '\n');

    int indices_selectionnes[MAX_MEMBRES] = {-1, -1, -1};
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf("\n\033[1;40m~ %d sur %d\033[0m", i + 1, MAX_MEMBRES);
        int index_personnage = choisir_personnage(nb_personnages);

        int deja_selectionne = 0;
        for (int j = 0; j < i; j++) {
            if (indices_selectionnes[j] == index_personnage) {
                deja_selectionne = 1;
                break;
            }
        }

        if (deja_selectionne == 1) {
            printf("\033[1;31m%s est deja sous vos ordres.\033[0m\n", personnages[index_personnage].nom);
            i--;
        } else {
            indices_selectionnes[i] = index_personnage;
            (*equipe).membres[i] = personnages[index_personnage];
            (*equipe).nb_membres++;
            printf("\033[1;39m%s pret au combat.\n\033[0m", personnages[index_personnage].nom);
        }
    }

    printf("\nAinsi, ");
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf("\033[1;39m%s, \033[0m", (*equipe).membres[i].nom);
    }
    printf("sont vos guerriers.\n\n");
}

void equipe_aleatoire(Personnage personnages[], int nb_personnages, Equipe equipe[]) {
    if (personnages == NULL || equipe == NULL) {
        printf("\033[1;31mErreur : tableau de personnages/equipes est NULL.\033[0m\n");
        exit(1);
    }
    if (nb_personnages < MAX_MEMBRES) {
        printf("\033[1;31mIl n'y a pas assez de combattants pour former une equipe !\033[0m\n");
        exit(1);
    }

    int tmp[MAX_MEMBRES] = {-1, -1, -1};
    int index_aleatoire;
    int doublon;

    for (int j = 0; j < MAX_MEMBRES; j++) {
        do {
            index_aleatoire = rand() % nb_personnages;
            doublon = 0;

            for (int i = 0; i < j; i++) {
                if (tmp[i] == index_aleatoire) {
                    doublon = 1;
                    break;
                }
            }
        } while (doublon);

        tmp[j] = index_aleatoire;
        equipe[0].membres[j] = personnages[index_aleatoire];
        equipe[0].nb_membres++;
    }
}

void afficher_equipe(Equipe equipe_joueur[], Equipe equipe_ennemi[]) {
    if (equipe_joueur == NULL || equipe_ennemi == NULL) {
        printf("\033[1;31mErreur : equipe joueur ou equipe ennemie invalide.\033[0m\n");
        return;
    }
    attendre(2);
    nettoyer();

    discours();

    printf("\n\033[1;40m\033[1;31m%s, %s, %s VS %s, %s, %s\n\033[0m\n", 
           equipe_joueur[0].membres[0].nom, 
           equipe_joueur[0].membres[1].nom, 
           equipe_joueur[0].membres[2].nom,
           equipe_ennemi[0].membres[0].nom, 
           equipe_ennemi[0].membres[1].nom, 
           equipe_ennemi[0].membres[2].nom);
}

void mode_univers(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[]) {
    if(entites == NULL || equipe_joueur == NULL || equipe_ennemi == NULL) {
        printf("\033[1;31mErreur : tableau de personnages/equipes est NULL.\033[0m\n");
        exit(1);
    }
    printf("\n\n\033[1;39mFormez votre equipe.\033[0m");
    choisir_equipe(entites, MAX_PERSONNAGES, &equipe_joueur[0]);

    chaudron();
    printf("\033[1;39mL'univers forme son equipe.\033[0m\n");
    equipe_aleatoire(entites, MAX_MEMBRES, equipe_ennemi);

    afficher_equipe(equipe_joueur, equipe_ennemi);

    Personnage equipe_joueur_membres[MAX_MEMBRES];
    Personnage equipe_ennemi_membres[MAX_MEMBRES];

    for (int i = 0; i < MAX_MEMBRES; i++) {
        equipe_joueur_membres[i] = equipe_joueur[0].membres[i];
        equipe_ennemi_membres[i] = equipe_ennemi[0].membres[i];
    }

    joueur_vs_univers(&equipe_joueur[0], equipe_joueur_membres, MAX_MEMBRES, 
                     equipe_ennemi_membres, MAX_MEMBRES);
}

void mode_versus(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[]) {
    if(entites == NULL || equipe_joueur == NULL || equipe_ennemi == NULL) {
        printf("\033[1;31mErreur : tableau de personnages/equipes est NULL.\033[0m\n");
        exit(1);
    }
    printf("\033[1;39mFormez votre equipe.\033[0m\n");
    choisir_equipe(entites, MAX_PERSONNAGES, &equipe_joueur[0]);

    printf("\033[1;39mFormez l'equipe adverse.\033[0m\n");
    choisir_equipe(entites, MAX_PERSONNAGES, &equipe_ennemi[0]);

    afficher_equipe(equipe_joueur, equipe_ennemi);

    Personnage equipe_joueur_membres[MAX_MEMBRES];
    Personnage equipe_ennemi_membres[MAX_MEMBRES];

    for (int i = 0; i < MAX_MEMBRES; i++) {
        equipe_joueur_membres[i] = equipe_joueur[0].membres[i];
        equipe_ennemi_membres[i] = equipe_ennemi[0].membres[i];
    }

    joueur_vs_joueur(equipe_joueur, equipe_joueur_membres, MAX_MEMBRES, 
                    equipe_ennemi, equipe_ennemi_membres, MAX_MEMBRES);
}

void charger(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[], int mode) {
    if (entites == NULL || equipe_joueur == NULL || equipe_ennemi == NULL) {
        printf("\033[1;31mErreur : tableau de personnages/equipes est NULL.\033[0m\n");
        exit(1);
    }
    int nb_personnages = afficher_personnages(entites, MAX_PERSONNAGES);

    if (mode == 0) {
        mode_univers(entites, equipe_joueur, equipe_ennemi);
    } else if (mode == 1) {
        mode_versus(entites, equipe_joueur, equipe_ennemi);
    }
    
    printf("\n");
}