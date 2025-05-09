#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int demander(int max) {
    int choix = -1;
    int resultat;

    do {
        printf("\033[0m\033[38;5;214m\033[3m\nFaites votre choix de 0 à %d ? \033[0m", max - 1);
        resultat = scanf("%d", &choix);

        if (resultat != 1 || choix < 0 || choix >= max) {
            printf("\033[1;39mVotre choix est hors de portée. Essayez à nouveau entre 0 et %d.\033[0m", max - 1);
            while (getchar() != '\n');
        }
    } while (resultat != 1 || choix < 0 || choix >= max);

    return choix;
}

int choisir_competence(Personnage *personnage, int index_personnage) {
    printf("\033[0m\033[38;5;214m\033[3m%s, de quelle compétence allez-vous faire preuve ?\n\033[0m", 
           personnage[index_personnage].nom);

    for (int i = 0; i < personnage[index_personnage].nb_competences; i++) {
        if (personnage[index_personnage].competences[i].nom == NULL || 
            personnage[index_personnage].competences[i].description == NULL) {
            printf("\033[1;31mErreur : compétence non initialisée pour l'index %d.\033[0m\n", i);
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
            printf("\033[1;31mCette compétence est en recharge. Choisissez une autre compétence.\033[0m\n");
        }
    } while (personnage[index_personnage].recharge[choix] > 0);

    return choix;
}

void attaquer_cible(Personnage *attaquant, Personnage *cible, int index_competence, int degats) {
    if (index_competence < 0 || index_competence >= MAX_COMPETENCES) {
        printf("\033[1;37mIndex de compétence invalide.\033[0m\n");
        exit(1);
    }

    int chance_esquive = cible->agilite - attaquant->agilite;
    if (chance_esquive > 0) {
        int valeur_aleatoire = rand() % 100; 
        if (valeur_aleatoire < chance_esquive) {
            printf("\033[1;37m%s a esquivé l'attaque de %s !\033[0m\n", cible->nom, attaquant->nom);
            return;
        }   
    }

    cible->pv_actuels -= degats;
    printf("\033[1;37m%s attaque %s avec %s et inflige %d dégâts !\033[0m\n", 
           attaquant->nom, cible->nom, attaquant->competences[index_competence].nom, degats);

    if (cible->pv_actuels <= 0) {
        printf("\033[1;37m%s a été vaincu !\033[0m\n", cible->nom);
        cible->pv_actuels = 0;
    } else {
        printf("\033[1;37m%s a encore %d PV restants.\033[0m\n", cible->nom, cible->pv_actuels);
    }
}

void appliquer_effet(Personnage *cible, const char *nom_effet, int valeur, int tours) {
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
    for (int i = 0; i < MAX_EFFETS; i++) {
        if (cible->effets[i].tours_restants > 0) {
            if (strcmp(cible->effets[i].nom, "saignement") == 0) {
                int saignement = cible->effets[i].valeur;
                cible->pv_actuels -= saignement;
                if (cible->pv_actuels < 0) cible->pv_actuels = 0;
                printf("\033[1;37m%s perd %d PV à cause de l'effet de saignement !\033[0m\n", 
                       cible->nom, saignement);
            }
            else if (strcmp(cible->effets[i].nom, "regeneration") == 0) {
                int regeneration = cible->effets[i].valeur;
                cible->pv_actuels += regeneration;
                if (cible->pv_actuels > cible->pv_max) cible->pv_actuels = cible->pv_max;
                printf("\033[1;37m%s regagne %d PV grâce à l'effet de regeneration !\033[0m\n", 
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
                printf("\033[1;37mL'effet %s sur %s a expiré !\033[0m\n", 
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
    for (int i = 0; i < personnage->nb_competences; i++) {
        if (personnage->recharge[i] > 0) {
            personnage->recharge[i]--;
        }
    }
}

void effet_cible(Personnage *attaquant, Personnage *cible, int index_competence) {
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
        printf("\033[1;37m%s réduit l'agilité de %s de %d points !\033[0m\n", 
               attaquant->nom, cible->nom, reduction);
    }
    else if (strcmp(competence.nom, "Rugissement bestial") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats < 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int reduction = cible[i].attaque * 0.3;
            appliquer_effet(&cible[i], "reduction d'attaque", reduction, competence.tours_actifs);
            printf("\033[1;37m%s réduit l'attaque de %s de %d points !\033[0m\n", 
                   attaquant->nom, cible[i].nom, reduction);
        }
    }
    else if (strcmp(competence.nom, "Ecrasement terrestre") == 0) {
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int degats = attaquant->attaque * competence.coefficient - cible[i].defense;
            if (degats < 0) degats = 0;
            attaquer_cible(attaquant, &cible[i], index_competence, degats);
        }
        printf("\033[1;37m%s inflige des dégâts de zone !\033[0m\n", attaquant->nom);
    }
    else if (strcmp(competence.nom, "Etoile glaciale") == 0) {
        int degats = attaquant->attaque * competence.coefficient - cible->defense;
        if (degats <= 0) degats = 0;
        attaquer_cible(attaquant, cible, index_competence, degats);
        int reduction = cible->vitesse * 0.3;
        appliquer_effet(cible, "reduction de vitesse", reduction, competence.tours_actifs);
        printf("\033[1;37m%s réduit la vitesse de %s de %d points !\033[0m\n", 
               attaquant->nom, cible->nom, reduction);
    }
    else if (strcmp(competence.nom, "Benediction lunaire") == 0) {
        int bonus_agi = attaquant->agilite * 0.5;
        int bonus_vit = attaquant->vitesse * 0.5;
        appliquer_effet(attaquant, "bonus d'agilite", bonus_agi, competence.tours_actifs);
        appliquer_effet(attaquant, "bonus de vitesse", bonus_vit, competence.tours_actifs);
        printf("\033[1;37m%s augmente son agilité de %d points et sa vitesse de %d points !\033[0m\n", 
               attaquant->nom, bonus_agi, bonus_vit);
    }
    else if (strcmp(competence.nom, "Pluie d'etoiles") == 0) {
        for (int i = 0; i < MAX_MEMBRES; i++) {
            int degats = attaquant->attaque * competence.coefficient - cible[i].defense;
            if (degats < 0) degats = 0;
            attaquer_cible(attaquant, &cible[i], index_competence, degats);
        }
        printf("\033[1;37m%s inflige des dégâts de zone !\033[0m\n", attaquant->nom);
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
        printf("\033[1;37m%s inflige des dégâts de zone !\033[0m\n", attaquant->nom);
        int degats_soi = attaquant->pv_max * 0.2;
        attaquant->pv_actuels -= degats_soi;
        if (attaquant->pv_actuels < 0) attaquant->pv_actuels = 0;
        printf("\033[1;37m%s perd %d PV en utilisant le Rituel interdit !\033[0m\n", 
               attaquant->nom, degats_soi);
    }
    else if (strcmp(competence.nom, "Marque du sang") == 0) {
        int reduction = cible->defense * 0.3;
        appliquer_effet(cible, "reduction de defense", reduction, competence.tours_actifs);
        printf("\033[1;37m%s réduit la défense de %s de %d points pour %d tours !\033[0m\n", 
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
        printf("\033[1;37m%s inflige des dégâts de zone !\033[0m\n", attaquant->nom);
    }

    attaquant->recharge[index_competence] = competence.tours_recharge;
}

void trier_vitesse(Personnage personnages[], int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = i+1; j < taille; j++) {
            if (personnages[i].vitesse < personnages[j].vitesse) {
                Personnage temp = personnages[i];
                personnages[i] = personnages[j];
                personnages[j] = temp;
            }
        }
    }
}

void tour_equipe(Equipe *equipe, Personnage *attaquant, Personnage equipe_ennemie[], int nb_ennemis) {
    printf("\n\033[1;37mDébut du tour de %s !\033[0m\n", equipe->nom);
    if (attaquant->pv_actuels <= 0) {
        printf("\033[1;31m%s est déjà vaincu et ne peut pas agir.\033[0m\n", attaquant->nom);
        return;
    }

    printf("Choisissez une cible parmi l'équipe adverse :\n");
    for (int i = 0; i < nb_ennemis; i++) {
        printf("\033[1;37m%d ~ %s (%d PV restants)\033[0m\n", 
               i, equipe_ennemie[i].nom, equipe_ennemie[i].pv_actuels);
    }
    int index_cible = demander(nb_ennemis);

    if (equipe_ennemie[index_cible].pv_actuels <= 0) {
        printf("\033[1;31mLa cible %s est déjà vaincue. Choisissez une autre cible.\033[0m\n", 
               equipe_ennemie[index_cible].nom);
        return;
    }

    int index_competence = choisir_competence(attaquant, 0);
    effet_cible(attaquant, &equipe_ennemie[index_cible], index_competence);
    mettre_a_jour_recharge(attaquant);
    mettre_a_jour_effets(attaquant);
    printf("\n\033[1;37mFin du tour de %s !\033[0m\n", equipe->nom);
}

void joueur_vs_univers(Equipe *equipe_joueur, Personnage *equipe_j, int nb_joueurs, 
                      Personnage *equipe_ennemie, int nb_ennemis) {
    Personnage tous_combattants[MAX_MEMBRES*2];
    int total_combattants = nb_joueurs + nb_ennemis;

    for (int i = 0; i < nb_joueurs; i++) {
        tous_combattants[i] = equipe_j[i];
        if (strlen(tous_combattants[i].nom) + strlen(" (e1)") < MAX_CARACTERES) {
            strcat(tous_combattants[i].nom, " (e1)");
        }
    }
    for (int i = 0; i < nb_ennemis; i++) {
        tous_combattants[nb_joueurs + i] = equipe_ennemie[i];
        if (strlen(tous_combattants[nb_joueurs + i].nom) + strlen(" (e2)") < MAX_CARACTERES) {
            strcat(tous_combattants[nb_joueurs + i].nom, " (e2)");
        }
    }

    trier_vitesse(tous_combattants, total_combattants);

    int continuer = 1;
    while (continuer) {
        for (int i = 0; i < total_combattants; i++) {
            if (tous_combattants[i].pv_actuels <= 0) continue;

            if (i < nb_joueurs) {
                tour_equipe(equipe_joueur, &tous_combattants[i], equipe_ennemie, nb_ennemis);
            } else {
                printf("\n\033[1;37mTour de l'univers !\033[0m\n");
                int index_cible = rand() % nb_joueurs;
                while (equipe_j[index_cible].pv_actuels <= 0) {
                    index_cible = rand() % nb_joueurs;
                }
                int index_competence = rand() % tous_combattants[i].nb_competences;
                effet_cible(&tous_combattants[i], &equipe_j[index_cible], index_competence);
                mettre_a_jour_recharge(&tous_combattants[i]);
                mettre_a_jour_effets(&tous_combattants[i]);
            }

            // Verifier fin de partie
            int joueurs_vivants = 0, ennemis_vivants = 0;
            for (int j = 0; j < nb_joueurs; j++) if (equipe_j[j].pv_actuels > 0) joueurs_vivants++;
            for (int j = 0; j < nb_ennemis; j++) if (equipe_ennemie[j].pv_actuels > 0) ennemis_vivants++;

            if (joueurs_vivants == 0) {
                printf("\n\033[1;31mL'equipe a perdu !\033[0m\n");
                defaite();
                continuer = 0;
                break;
            } else if (ennemis_vivants == 0) {
                printf("\n\033[1;32mL'univers a perdu !\033[0m\n");
                victoire();
                continuer = 0;
                break;
            }
        }
    }
}

void joueur_vs_joueur(Equipe *equipe1, Personnage *equipe_j1, int nb_joueurs1,
                     Equipe *equipe2, Personnage *equipe_j2, int nb_joueurs2) {
    Personnage tous_combattants[MAX_MEMBRES * 2];
    int total_combattants = nb_joueurs1 + nb_joueurs2;

    for (int i = 0; i < nb_joueurs1; i++) {
        tous_combattants[i] = equipe_j1[i];
        if (strlen(tous_combattants[i].nom) + strlen(" (e1)") < MAX_CARACTERES) {
            strcat(tous_combattants[i].nom, " (e1)");
        }
    }
    for (int i = 0; i < nb_joueurs2; i++) {
        tous_combattants[nb_joueurs1 + i] = equipe_j2[i];
        if (strlen(tous_combattants[nb_joueurs1 + i].nom) + strlen(" (e2)") < MAX_CARACTERES) {
            strcat(tous_combattants[nb_joueurs1 + i].nom, " (e2)");
        }
    }

    trier_vitesse(tous_combattants, total_combattants);

    int continuer = 1;
    while (continuer) {
        for (int i = 0; i < total_combattants; i++) {
            if (tous_combattants[i].pv_actuels <= 0) continue;

            if (i < nb_joueurs1) {
                tour_equipe(equipe1, &tous_combattants[i], equipe_j2, nb_joueurs2);
            } else {
                tour_equipe(equipe2, &tous_combattants[i], equipe_j1, nb_joueurs1);
            }

            // Verifier fin de partie
            int equipe1_vivants = 0, equipe2_vivants = 0;
            for (int j = 0; j < nb_joueurs1; j++) if (equipe_j1[j].pv_actuels > 0) equipe1_vivants++;
            for (int j = 0; j < nb_joueurs2; j++) if (equipe_j2[j].pv_actuels > 0) equipe2_vivants++;

            if (equipe1_vivants == 0) {
                printf("\n\033[1;31mL'equipe 1 a perdu !\033[0m\n");
                defaite();
                printf("\n\033[1;32mL'equipe 2 a gagne !\033[0m\n");
                victoire();
                continuer = 0;
                break;
            } else if (equipe2_vivants == 0) {
                printf("\n\033[1;31mL'equipe 2 a perdu !\033[0m\n");
                defaite();
                printf("\n\033[1;32mL'equipe 1 a gagne !\033[0m\n");
                victoire();
                continuer = 0;
                break;
            }
        }
    }
}

void robot_vs_robot(Equipe *equipe1, Personnage *robots1, int nb_robots1,
                   Equipe *equipe2, Personnage *robots2, int nb_robots2) {
    Personnage tous_combattants[MAX_MEMBRES * 2];
    int total_combattants = nb_robots1 + nb_robots2;

    for (int i = 0; i < nb_robots1; i++) {
        tous_combattants[i] = robots1[i];
        if (strlen(tous_combattants[i].nom) + strlen(" (e1)") < MAX_CARACTERES) {
            strcat(tous_combattants[i].nom, " (e1)");
        }
    }
    for (int i = 0; i < nb_robots2; i++) {
        tous_combattants[nb_robots1 + i] = robots2[i];
        if (strlen(tous_combattants[nb_robots1 + i].nom) + strlen(" (e2)") < MAX_CARACTERES) {
            strcat(tous_combattants[nb_robots1 + i].nom, " (e2)");
        }
    }

    trier_vitesse(tous_combattants, total_combattants);

    int continuer = 1;
    while (continuer) {
        for (int i = 0; i < total_combattants; i++) {
            if (tous_combattants[i].pv_actuels <= 0) continue;

            printf("\n\033[1;37mTour de %s !\033[0m\n", tous_combattants[i].nom);
            
            if (i < nb_robots1) {
                int index_cible = rand() % nb_robots2;
                while (robots2[index_cible].pv_actuels <= 0) {
                    index_cible = rand() % nb_robots2;
                }
                int index_competence = rand() % tous_combattants[i].nb_competences;
                effet_cible(&tous_combattants[i], &robots2[index_cible], index_competence);
            } else {
                int index_cible = rand() % nb_robots1;
                while (robots1[index_cible].pv_actuels <= 0) {
                    index_cible = rand() % nb_robots1;
                }
                int index_competence = rand() % tous_combattants[i].nb_competences;
                effet_cible(&tous_combattants[i], &robots1[index_cible], index_competence);
            }
            mettre_a_jour_recharge(&tous_combattants[i]);
            mettre_a_jour_effets(&tous_combattants[i]);

            // Verifier fin de partie
            int equipe1_vivants = 0, equipe2_vivants = 0;
            for (int j = 0; j < nb_robots1; j++) if (robots1[j].pv_actuels > 0) equipe1_vivants++;
            for (int j = 0; j < nb_robots2; j++) if (robots2[j].pv_actuels > 0) equipe2_vivants++;

            if (equipe1_vivants == 0) {
                printf("\n\033[1;31mL'equipe 1 a perdu !\033[0m\n");
                defaite();
                printf("\n\033[1;32mL'equipe 2 a gagne !\033[0m\n");
                victoire();
                continuer = 0;
                break;
            } else if (equipe2_vivants == 0) {
                printf("\n\033[1;31mL'equipe 2 a perdu !\033[0m\n");
                defaite();
                printf("\n\033[1;32mL'equipe 1 a gagne !\033[0m\n");
                victoire();
                continuer = 0;
                break;
            }
        }
    }
}