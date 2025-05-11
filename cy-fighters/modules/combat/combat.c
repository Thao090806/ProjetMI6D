#include "combat.h"
#include "../logique/logique.h"
#include "../script/script.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int demander(int max) {
    /*
        * Demande à l'utilisateur de choisir un nombre entre 0 et max-1.
        * 
        * Paramètres :
        * - max : valeur maximale (exclusif)
        * 
        * Retourne :
        * - Le choix de l'utilisateur
    */
    if (max <= 0) {
        printf("\033[1;31mErreur : la valeur max doit etre superieure a 0.\033[0m\n");
        exit(1);
    }
    int choix = -1;
    int resultat;

    do {
        printf("\033[0m\033[38;5;214m\033[3m\nFaites votre choix de 0 a %d ? \033[0m", max - 1);
        resultat = scanf("%d", &choix);

        if (resultat != 1 || choix < 0 || choix >= max) {
            printf("\033[1;39mVotre choix est hors de portee. Essayez a nouveau entre 0 et %d.\033[0m", max - 1);
            while (getchar() != '\n');
        }
    } while (resultat != 1 || choix < 0 || choix >= max);

    return choix;
}

int choisir_competence(Personnage *personnage, int index_personnage) {
    /*
        * Choisit une compétence à utiliser par le personnage.
        * 
        * Paramètres :
        * - personnage : tableau de personnages
        * - index_personnage : index du personnage dans le tableau
    */
    if (personnage == NULL || index_personnage < 0 || index_personnage >= MAX_MEMBRES) {
        printf("\033[1;31mErreur : personnage ou index invalide.\033[0m\n");
        exit(1);
    }
    printf("\033[0m\033[38;5;214m\033[3m%s, de quelle competence allez-vous faire preuve ?\n\033[0m", 
           personnage[index_personnage].nom);

    for (int i = 0; i < personnage[index_personnage].nb_competences; i++) {
        if (personnage[index_personnage].competences[i].nom == NULL || 
            personnage[index_personnage].competences[i].description == NULL) {
            printf("\033[1;31mErreur : competence non initialisee pour l'index %d.\033[0m\n", i);
            continue;
        }

        if (personnage[index_personnage].recharge[i] > 0) {
            printf("\033[1;31m%d ~ %s (En recharge : %d tours restants)\033[0m\n",
                   i, personnage[index_personnage].competences[i].nom, 
                   personnage[index_personnage].recharge[i]);
        } else {
            printf("\033[1;37m%d ~ %s\033[0m : %s\n",
                   i, personnage[index_personnage].competences[i].nom, 
                   personnage[index_personnage].competences[i].description);
        }
    }

    int choix;
    do {
        choix = demander(personnage[index_personnage].nb_competences);
        if (personnage[index_personnage].recharge[choix] > 0) {
            printf("\033[1;31mCette competence est en recharge. Choisissez une autre competence.\033[0m\n");
        }
    } while (personnage[index_personnage].recharge[choix] > 0);

    return choix;
}

void attaquer_cible(Personnage *attaquant, Personnage *cible, int index_competence, int degats) {
    /*
        * Applique les dégâts à la cible.
        * 
        * Paramètres :
        * - attaquant : pointeur vers le personnage attaquant
        * - cible : pointeur vers le personnage cible
        * - index_competence : index de la compétence utilisée
        * - degats : dégâts infligés
        
    */
    if (attaquant == NULL || cible == NULL || attaquant->nom[0] == '\0' || cible->nom[0] == '\0') {
        printf("\033[1;31mErreur: cible ou attaquant invalide\033[0m\n");
        return;
    }

    if ((rand() % 100) < (cible->agilite - attaquant->agilite)) {
        printf("\033[1;37m%s a esquive l'attaque de %s!\033[0m\n", cible->nom, attaquant->nom);
        return;
    }

    degats = (degats < 0) ? 0 : degats;  
    cible->pv_actuels -= degats;

    printf("\033[1;37m%s attaque %s avec %s (%d degats)\033[0m\n",
           attaquant->nom, cible->nom, 
           attaquant->competences[index_competence].nom, 
           degats);

    if (cible->pv_actuels <= 0) {
        cible->pv_actuels = 0;
        printf("\033[1;31m%s a ete vaincu!\033[0m\n", cible->nom);
    } else {
        printf("PV restants: %d\n", cible->pv_actuels);
    }
}

void appliquer_effet(Personnage *cible, const char *nom_effet, int valeur, int tours) {
    /*
        * Applique un effet sur le personnage cible.
        * 
        * Paramètres :
        * - cible : pointeur vers le personnage
        * - nom_effet : nom de l'effet
        * - valeur : valeur de l'effet
        * - tours : nombre de tours restants
    */
    if (cible == NULL || nom_effet == NULL) {
        printf("\033[1;31mErreur : cible ou nom d'effet invalide.\033[0m\n");
        exit(1);
    }

    if (cible == NULL || nom_effet == NULL || tours <= 0) {
        printf("Erreur: cible ou nom d'effet invalide.\n");
        exit(1);
    }

    if (valeur < 0) valeur = 0;
    else if (valeur > 1000) valeur = 1000;

    for (int i = 0; i < MAX_EFFETS; i++) {
        if (cible->effets[i].tours_restants == 0) {
            strcpy(cible->effets[i].nom, nom_effet);
            cible->effets[i].valeur = valeur;
            cible->effets[i].tours_restants = tours;
            printf("\033[1;37m%s subit l'effet %s de %d pour %d tours !\033[0m\n", 
                   cible->nom, nom_effet, valeur, tours);
            return;
        }
    }
    printf("\033[1;37mImpossible d'appliquer l'effet %s sur %s, pas de place disponible.\033[0m\n", 
           nom_effet, cible->nom);
}

void mettre_a_jour_effets(Personnage *cible) {
    /*
        * Met à jour les effets actifs sur le personnage.
        * 
        * Paramètres :
        * - cible : pointeur vers le personnage
    */
    if (cible == NULL) {
        printf("\033[1;31mErreur : cible invalide.\033[0m\n");
        exit(1);
    }
    for (int i = 0; i < MAX_EFFETS; i++) {
        if (cible->effets[i].tours_restants > 0) {
            if (strcmp(cible->effets[i].nom, "saignement") == 0) {
                int saignement = cible->effets[i].valeur;
                cible->pv_actuels -= saignement;
                if (cible->pv_actuels < 0) cible->pv_actuels = 0;
                printf("\033[1;37m%s perd %d PV a cause de l'effet de saignement !\033[0m\n", 
                       cible->nom, saignement);
            }
            else if (strcmp(cible->effets[i].nom, "regeneration") == 0) {
                int regeneration = cible->effets[i].valeur;
                cible->pv_actuels += regeneration;
                if (cible->pv_actuels > cible->pv_max) cible->pv_actuels = cible->pv_max;
                printf("\033[1;37m%s regagne %d PV grace a l'effet de regeneration !\033[0m\n", 
                       cible->nom, regeneration);
            }
            else if (strcmp(cible->effets[i].nom, "bonus d'attaque") == 0) {
                cible->attaque += cible->effets[i].valeur;
            }
            else if (strcmp(cible->effets[i].nom, "reduction d'attaque") == 0) {
                cible->attaque -= cible->effets[i].valeur;
                if (cible->attaque < 0) cible->attaque = 0;
            }
            else if (strcmp(cible->effets[i].nom, "reduction de defense") == 0) {
                cible->defense -= cible->effets[i].valeur;
                if (cible->defense < 0) cible->defense = 0;
            }
            else if (strcmp(cible->effets[i].nom, "bonus d'agilite") == 0) {
                cible->agilite += cible->effets[i].valeur;
            }
            else if (strcmp(cible->effets[i].nom, "reduction d'agilite") == 0) {
                cible->agilite -= cible->effets[i].valeur;
                if (cible->agilite < 0) cible->agilite = 0;
            }
            else if (strcmp(cible->effets[i].nom, "bonus de vitesse") == 0) {
                cible->vitesse += cible->effets[i].valeur;
            }
            else if (strcmp(cible->effets[i].nom, "reduction de vitesse") == 0) {
                cible->vitesse -= cible->effets[i].valeur;
                if (cible->vitesse < 0) cible->vitesse = 0;
            }

            cible->effets[i].tours_restants--;
            if (cible->effets[i].tours_restants <= 0) {
                printf("\033[1;37mL'effet %s sur %s a expire !\033[0m\n", 
                       cible->effets[i].nom, cible->nom);

                if (strcmp(cible->effets[i].nom, "bonus d'attaque") == 0) {
                    cible->attaque -= cible->effets[i].valeur;
                }
                else if (strcmp(cible->effets[i].nom, "reduction d'attaque") == 0) {
                    cible->attaque += cible->effets[i].valeur;
                }
                else if (strcmp(cible->effets[i].nom, "bonus d'agilite") == 0) {
                    cible->agilite -= cible->effets[i].valeur;
                }
                else if (strcmp(cible->effets[i].nom, "reduction d'agilite") == 0) {
                    cible->agilite += cible->effets[i].valeur;
                }
                else if (strcmp(cible->effets[i].nom, "bonus de vitesse") == 0) {
                    cible->vitesse -= cible->effets[i].valeur;
                }
                else if (strcmp(cible->effets[i].nom, "reduction de vitesse") == 0) {
                    cible->vitesse += cible->effets[i].valeur;
                }
                else if (strcmp(cible->effets[i].nom, "reduction de defense") == 0) {
                    cible->defense += cible->effets[i].valeur;
                }

                cible->effets[i].nom[0] = '\0';
                cible->effets[i].valeur = 0;
            }
        }
    }
}

void mettre_a_jour_recharge(Personnage *personnage) {  
    /*
        * Met à jour le temps de recharge des compétences du personnage.
        * 
        * Paramètres :
        * - personnage : pointeur vers le personnage
    */
    if (personnage == NULL) {
        printf("\033[1;31mErreur : personnage invalide.\033[0m\n");
        exit(1);
    }
    for (int i = 0; i < personnage->nb_competences; i++) {
        if (personnage->recharge[i] > 0) {
            personnage->recharge[i]--;
        }
    }
}

void effet_cible(Personnage *attaquant, Personnage *cible, int index_competence) {
    /*
        * Fonction d'effet de compétence sur la cible.
        * 
        * Paramètres :
        * - attaquant : pointeur vers le personnage attaquant
        * - cible : pointeur vers le personnage cible
        * - index_competence : index de la compétence utilisée
    */
    if (attaquant == NULL || cible == NULL || index_competence < 0 || index_competence >= MAX_COMPETENCES) {
        printf("\033[1;31mErreur : attaquant ou cible invalide.\033[0m\n");
        exit(1);
    }
    Competence competence = attaquant->competences[index_competence];
    printf("\033[1;37m%s utilise %s sur %s !\033[0m\n", 
           attaquant->nom, competence.nom, cible->nom);

    if (strcmp(competence.nom, "Coup du vagabond") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats <= 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
    }
    else if (strcmp(competence.nom, "Determination") == 0) {
        int bonus = attaquant->attaque * 0.5;
        attaquant->attaque += bonus;
        appliquer_effet(attaquant, "bonus d'attaque", bonus, competence.tours_actifs);
        printf("\033[1;37m%s augmente son attaque de %d points pour %d tours !\033[0m\n", 
               attaquant->nom, bonus, competence.tours_actifs);
    }
    else if (strcmp(competence.nom, "Frappe decisive") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats < 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
    }
    else if (strcmp(competence.nom, "Danse de lames") == 0) {
        int degats = (attaquant->attaque * competence.coefficient - cible->defense) / 3;
        if (degats < 0) degats = 0;
        for (int i = 0; i < 3; i++) {
            attaquer_cible(attaquant, cible, index_competence, degats);
        }
    }
    else if (strcmp(competence.nom, "Regeneration") == 0) {
        int soin = attaquant->pv_max * 0.2;
        attaquant->pv_actuels += soin;
        if (attaquant->pv_actuels > attaquant->pv_max) attaquant->pv_actuels = attaquant->pv_max;
        appliquer_effet(attaquant, "regeneration", soin, competence.tours_actifs);
        printf("\033[1;37m%s restaure %d PV !\033[0m\n", attaquant->nom, soin);
    }
    else if (strcmp(competence.nom, "Lame ecarlate") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats < 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        int saignement = cible->pv_max * 0.1;
        appliquer_effet(cible, "saignement", saignement, competence.tours_actifs);
        printf("\033[1;37m%s applique un effet de saignement sur %s !\033[0m\n", 
               attaquant->nom, cible->nom);
    }
    else if (strcmp(competence.nom, "Frappe colossale") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats < 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        int reduction = cible->agilite * 0.5;
        appliquer_effet(cible, "reduction d'agilite", reduction, competence.tours_actifs);
        printf("\033[1;37m%s reduit l'agilite de %s de %d points !\033[0m\n", 
               attaquant->nom, cible->nom, reduction);
    }
    else if (strcmp(competence.nom, "Rugissement bestial") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats < 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int reduction = cible[i].attaque * 0.3;
            appliquer_effet(&cible[i], "reduction d'attaque", reduction, competence.tours_actifs);
            printf("\033[1;37m%s reduit l'attaque de %s de %d points !\033[0m\n", 
                   attaquant->nom, cible[i].nom, reduction);
        }
    }
    else if (strcmp(competence.nom, "Ecrasement terrestre") == 0) {
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int degats = attaquant->attaque * competence.coefficient - cible[i].defense;
            if (degats < 0) degats = 0;
            attaquer_cible(attaquant, &cible[i], index_competence, degats);
        }
        printf("\033[1;37m%s inflige des degats de zone !\033[0m\n", attaquant->nom);
    }
    else if (strcmp(competence.nom, "Etoile glaciale") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats <= 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        int reduction = cible->vitesse * 0.3;
        appliquer_effet(cible, "reduction de vitesse", reduction, competence.tours_actifs);
        printf("\033[1;37m%s reduit la vitesse de %s de %d points !\033[0m\n", 
               attaquant->nom, cible->nom, reduction);
    }
    else if (strcmp(competence.nom, "Benediction lunaire") == 0) {
        int bonus_agi = attaquant->agilite * 0.5;
        int bonus_vit = attaquant->vitesse * 0.5;
        appliquer_effet(attaquant, "bonus d'agilite", bonus_agi, competence.tours_actifs);
        appliquer_effet(attaquant, "bonus de vitesse", bonus_vit, competence.tours_actifs);
        printf("\033[1;37m%s augmente son agilite de %d points et sa vitesse de %d points !\033[0m\n", 
               attaquant->nom, bonus_agi, bonus_vit);
    }
    else if (strcmp(competence.nom, "Pluie d'etoiles") == 0) {
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int degats = attaquant->attaque * competence.coefficient - cible[i].defense;
            if (degats < 0) degats = 0;
            attaquer_cible(attaquant, &cible[i], index_competence, degats);
        }
        printf("\033[1;37m%s inflige des degats de zone !\033[0m\n", attaquant->nom);
    }
    else if (strcmp(competence.nom, "Flammes sanglantes") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats < 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        int saignement = cible->pv_max * 0.1;
        appliquer_effet(cible, "saignement", saignement, competence.tours_actifs);
        printf("\033[1;37m%s applique un effet de saignement sur %s !\033[0m\n", 
               attaquant->nom, cible->nom);
    }
    else if (strcmp(competence.nom, "Rituel interdit") == 0) {
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int degats = attaquant->attaque * competence.coefficient - cible[i].defense;
            if (degats < 0) degats = 0;
            attaquer_cible(attaquant, &cible[i], index_competence, degats);
        }
        printf("\033[1;37m%s inflige des degats de zone !\033[0m\n", attaquant->nom);
        int degats_soi = attaquant->pv_max * 0.2;
        attaquant->pv_actuels -= degats_soi;
        if (attaquant->pv_actuels < 0) attaquant->pv_actuels = 0;
        printf("\033[1;37m%s perd %d PV en utilisant le Rituel interdit !\033[0m\n", 
               attaquant->nom, degats_soi);
    }
    else if (strcmp(competence.nom, "Marque du sang") == 0) {
        int reduction = cible->defense * 0.3;
        appliquer_effet(cible, "reduction de defense", reduction, competence.tours_actifs);
        printf("\033[1;37m%s reduit la defense de %s de %d points pour %d tours !\033[0m\n", 
               attaquant->nom, cible->nom, reduction, competence.tours_actifs);
    }
    else if (strcmp(competence.nom, "Lame sacree") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats <= 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
    }
    else if (strcmp(competence.nom, "Pluie de lames") == 0) {
        int degats = (attaquant->attaque * competence.coefficient - cible->defense) / 3;
        if (degats < 0) degats = 0;
        for (int i = 0; i < 3; i++) {
            attaquer_cible(attaquant, cible, index_competence, degats);
        }
    }
    else if (strcmp(competence.nom, "Jugement divin") == 0) {
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int degats = attaquant->attaque * competence.coefficient - cible[i].defense;
            if (degats < 0) degats = 0;
            attaquer_cible(attaquant, &cible[i], index_competence, degats);
        }
        printf("\033[1;37m%s inflige des degats de zone !\033[0m\n", attaquant->nom);
    }

    attaquant->recharge[index_competence] = competence.tours_recharge;
}

void tour_equipe_joueur(Equipe *equipe, Personnage *attaquant, Personnage equipe_ennemie[], int nb_ennemis) {
    /*
        * Procedure de combat pour l'équipe du joueur.
        * Le joueur choisit une cible parmi les ennemis et utilise une compétence.
        * 
        * Paramètres :
        * - equipe : pointeur vers l'équipe du joueur
        * - attaquant : pointeur vers le personnage attaquant
        * - equipe_ennemie : tableau de personnages ennemis
        * - nb_ennemis : nombre d'ennemis dans l'équipe ennemie
    */
    printf("\n\033[1;37mTour de %s (%s) !\033[0m\n", equipe->nom, attaquant->nom);
    
    if (attaquant->pv_actuels <= 0) {
        printf("\033[1;31m%s est deja vaincu et ne peut pas agir.\033[0m\n", attaquant->nom);
        return;
    }

    // Choix de la cible
    printf("Choisissez une cible parmi l'univers :\n");
    for (int i = 0; i < nb_ennemis; i++) {
        printf("\033[1;37m%d ~ %s (%d PV restants)\033[0m\n", 
               i, equipe_ennemie[i].nom, equipe_ennemie[i].pv_actuels);
    }
    int index_cible = demander(nb_ennemis);

    if (equipe_ennemie[index_cible].pv_actuels <= 0) {
        printf("\033[1;31mLa cible %s est deja vaincue. Choisissez une autre cible.\033[0m\n", 
               equipe_ennemie[index_cible].nom);
        return;
    }

    // Choix de la compétence
    int index_competence = choisir_competence(attaquant, 0);
    effet_cible(attaquant, &equipe_ennemie[index_cible], index_competence);
}

void tour_univers(Personnage *attaquant, Personnage equipe_joueur[], int nb_joueurs, int difficulte) {
    /*
        * Procedure de combat pour l'univers.
        * L'univers choisit une cible parmi les joueurs et utilise une compétence.
        * 
        * Paramètres :
        * - attaquant : pointeur vers le personnage de l'univers
        * - equipe_joueur : tableau de personnages de l'équipe du joueur
        * - nb_joueurs : nombre de joueurs dans l'équipe du joueur
        * - difficulte : niveau de difficulté (0: Débutant, 1: Facile, 2: Normal)
    */
    printf("\n\033[1;31mTour de l'univers (%s) !\033[0m\n", attaquant->nom);
    
    if (attaquant->pv_actuels <= 0) {
        printf("\033[1;31m%s est deja vaincu et ne peut pas agir.\033[0m\n", attaquant->nom);
        return;
    }

    // Choix de la cible par l'univers
    int index_cible = 0;
    if (difficulte == 0) { // Débutant - aléatoire
        do {
            index_cible = rand() % nb_joueurs;
        } while (equipe_joueur[index_cible].pv_actuels <= 0);
    } else { // Facile/Normal - cible la plus faible
        int min_pv = 1000000;
        for (int j = 0; j < nb_joueurs; j++) {
            if (equipe_joueur[j].pv_actuels > 0 && equipe_joueur[j].pv_actuels < min_pv) {
                min_pv = equipe_joueur[j].pv_actuels;
                index_cible = j;
            }
        }
    }

    // Choix de la compétence par l'univers
    int index_competence = 0;
    if (difficulte == 2) { // Normal - privilégie compétences spéciales
        if (attaquant->nb_competences > 2 && attaquant->recharge[2] == 0) {
            index_competence = 2;
        } else if (attaquant->nb_competences > 1 && attaquant->recharge[1] == 0) {
            index_competence = 1;
        }
    } // Sinon utilise la compétence de base (index 0)

    printf("L'univers choisit %s comme cible et utilise %s !\n",
           equipe_joueur[index_cible].nom, attaquant->competences[index_competence].nom);
    
    effet_cible(attaquant, &equipe_joueur[index_cible], index_competence);
}

void joueur_vs_univers(Equipe *equipe_joueur, Personnage equipe_j[], int nb_joueurs, Personnage equipe_univers[], int nb_univers, int difficulte) {
    /*
        * Procedure de combat entre une équipe de joueurs et une équipe d'univers.
        * Chaque équipe joue à tour de rôle, en choisissant un personnage et une compétence.
        * Le combat continue jusqu'à ce qu'une équipe soit vaincue.
        * 
        * Paramètres :
        * - equipe_joueur : pointeur vers l'équipe du joueur
        * - equipe_j : tableau de personnages de l'équipe du joueur
        * - nb_joueurs : nombre de joueurs dans l'équipe du joueur
        * - equipe_univers : tableau de personnages de l'équipe de l'univers
        * - nb_univers : nombre de personnages dans l'équipe de l'univers
    */
    int tour = 0; // 0 pour joueur, 1 pour univers
    int index_joueur = 0, index_univers = 0;
    
    int continuer = 1;
    while (continuer) {
        
        if (tour == 0) { // Tour du joueur
            // Trouver le prochain personnage vivant
            while (index_joueur < nb_joueurs && equipe_j[index_joueur].pv_actuels <= 0) {
                index_joueur++;
            }
            
            if (index_joueur < nb_joueurs) {
                printf("\n\033[1;36mTour de votre equipe (%s) !\033[0m\n", equipe_joueur->nom);
                tour_equipe_joueur(equipe_joueur, &equipe_j[index_joueur], equipe_univers, nb_univers);
                mettre_a_jour_recharge(&equipe_j[index_joueur]);
                mettre_a_jour_effets(&equipe_j[index_joueur]);
                index_joueur++;
            }
            tour = 1;
        } else { // Tour de l'univers
            // Trouver le prochain personnage vivant
            while (index_univers < nb_univers && equipe_univers[index_univers].pv_actuels <= 0) {
                index_univers++;
            }
            
            if (index_univers < nb_univers) {
                printf("\n\033[1;31mTour de l'univers (%s) !\033[0m\n", equipe_univers[index_univers].nom);
                tour_univers(&equipe_univers[index_univers], equipe_j, nb_joueurs, difficulte);
                mettre_a_jour_recharge(&equipe_univers[index_univers]);
                mettre_a_jour_effets(&equipe_univers[index_univers]);
                index_univers++;
            }
            tour = 0;
        }
        
        // Réinitialiser les index si nécessaire
        if (index_joueur >= nb_joueurs) index_joueur = 0;
        if (index_univers >= nb_univers) index_univers = 0;
        
        // Vérifier fin de partie
        int joueurs_vivants = 0, univers_vivants = 0;
        for (int j = 0; j < nb_joueurs; j++) {
            if (equipe_j[j].pv_actuels > 0) joueurs_vivants++;
        }
        for (int j = 0; j < nb_univers; j++) {
            if (equipe_univers[j].pv_actuels > 0) univers_vivants++;
        }

        if (joueurs_vivants == 0) {
            printf("\n\033[1;31mVous avez ete vaincu par l'univers !\033[0m\n");
            defaite();
            continuer = 0;
        } else if (univers_vivants == 0) {
            printf("\n\033[1;32mVous avez triomphe de l'univers !\033[0m\n");
            victoire();
            continuer = 0;
        }
        
        attendre(2); // Pause pour lire les résultats
    }
}

void joueur_vs_joueur(Equipe *equipe1, Personnage equipe_j1[], int nb_joueurs1,
                     Equipe *equipe2, Personnage equipe_j2[], int nb_joueurs2) {
    /*
        * Procedure de combat entre deux équipes de joueurs.
        * Chaque équipe joue à tour de rôle, en choisissant un personnage et une compétence.
        * Le combat continue jusqu'à ce qu'une équipe soit vaincue.
        * 
        * Paramètres :
        * - equipe1 : pointeur vers la première équipe
        * - equipe_j1 : tableau de personnages de l'équipe 1
        * - nb_joueurs1 : nombre de joueurs dans l'équipe 1
        * - equipe2 : pointeur vers la deuxième équipe
        * - equipe_j2 : tableau de personnages de l'équipe 2
        * - nb_joueurs2 : nombre de joueurs dans l'équipe 
    */
    int tour = 0; // 0 pour équipe1, 1 pour équipe2
    int index_equipe1 = 0, index_equipe2 = 0;
    
    int continuer = 1;
    while (continuer) {
        
        if (tour == 0) { // Tour de l'équipe 1
            // Trouver le prochain personnage vivant
            while (index_equipe1 < nb_joueurs1 && equipe_j1[index_equipe1].pv_actuels <= 0) {
                index_equipe1++;
            }
            
            if (index_equipe1 < nb_joueurs1) {
                printf("\n\033[1;36mTour de %s (%s) !\033[0m\n", equipe1->nom, equipe_j1[index_equipe1].nom);
                tour_equipe_joueur(equipe1, &equipe_j1[index_equipe1], equipe_j2, nb_joueurs2);
                mettre_a_jour_recharge(&equipe_j1[index_equipe1]);
                mettre_a_jour_effets(&equipe_j1[index_equipe1]);
                index_equipe1++;
            }
            tour = 1;
        } else { // Tour de l'équipe 2
            // Trouver le prochain personnage vivant
            while (index_equipe2 < nb_joueurs2 && equipe_j2[index_equipe2].pv_actuels <= 0) {
                index_equipe2++;
            }
            
            if (index_equipe2 < nb_joueurs2) {
                printf("\n\033[1;35mTour de %s (%s) !\033[0m\n", equipe2->nom, equipe_j2[index_equipe2].nom);
                tour_equipe_joueur(equipe2, &equipe_j2[index_equipe2], equipe_j1, nb_joueurs1);
                mettre_a_jour_recharge(&equipe_j2[index_equipe2]);
                mettre_a_jour_effets(&equipe_j2[index_equipe2]);
                index_equipe2++;
            }
            tour = 0;
        }
        
        // Réinitialiser les index si nécessaire
        if (index_equipe1 >= nb_joueurs1) index_equipe1 = 0;
        if (index_equipe2 >= nb_joueurs2) index_equipe2 = 0;
        
        // Vérifier fin de partie
        int equipe1_vivants = 0, equipe2_vivants = 0;
        for (int j = 0; j < nb_joueurs1; j++) {
            if (equipe_j1[j].pv_actuels > 0) equipe1_vivants++;
        }
        for (int j = 0; j < nb_joueurs2; j++) {
            if (equipe_j2[j].pv_actuels > 0) equipe2_vivants++;
        }

        if (equipe1_vivants == 0) {
            printf("\n\033[1;31m%s a ete vaincue !\033[0m\n", equipe1->nom);
            defaite();
            printf("\n\033[1;32m%s triomphe !\033[0m\n", equipe2->nom);
            continuer = 0;
        } else if (equipe2_vivants == 0) {
            printf("\n\033[1;31m%s a ete vaincue !\033[0m\n", equipe2->nom);
            defaite();
            printf("\n\033[1;32m%s triomphe !\033[0m\n", equipe1->nom);
            continuer = 0;
        }
        
        attendre(2); // Pause pour lire les résultats
    }
}