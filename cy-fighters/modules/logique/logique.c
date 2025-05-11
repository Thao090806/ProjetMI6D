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
    /*
    La fonction attendre() suspend l’exécution du programme pendant un certain nombre de secondes.
    Elle prend en paramètre un entier représentant le nombre de secondes à attendre.
    Selon le système d’exploitation, elle utilise Sleep() (Windows) ou sleep() (Unix) pour effectuer la pause.
    */
    if (secondes < 0) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
        exit(1);
    }
    #ifdef _WIN32
        Sleep(secondes * 1000);
    #else
        sleep(secondes);
    #endif
}

void nettoyer() {
    /*
    La fonction nettoyer() efface l’écran de la console.
    Elle ne prend aucun paramètre.
    Elle utilise system("cls") sur Windows ou system("clear") sur Unix pour nettoyer l’affichage.
    */
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int afficher_personnages(Personnage personnages[], int nb_personnages) {
    /*
    La fonction afficher_personnages() affiche la liste des personnages disponibles dans le jeu.
    Elle prend en paramètre un tableau de Personnage et le nombre de personnages à afficher.
    Elle parcourt le tableau, affiche les caractéristiques et compétences de chaque personnage, puis retourne le nombre de personnages affichés.
    */
    if(personnages == NULL || nb_personnages <= 0) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
        exit(1);
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
                    printf("\n (\033[1;33m%s\033[0m) ", personnages[i].competences[j].nom);
                if ( personnages[i].competences[j].description && strlen(personnages[i].competences[j].description) > 0)
                    printf("%s", personnages[i].competences[j].description);
            }
        }
        
        printf("\n");
    }

    return nb_personnages;
}
int choisir_personnage(int nb_personnages) {
    /*
        * La fonction choisir_personnage() demande à l'utilisateur de choisir un personnage parmi ceux disponibles.
        * Elle prend en paramètre le nombre de personnages disponibles.
        * Si le nombre de personnages est inférieur ou égal à 0, elle affiche un message d'erreur et quitte le programme.
        * Sinon, elle demande à l'utilisateur de choisir un personnage et retourne l'index du personnage choisi.
    */
    if (nb_personnages <= 0) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
        exit(1);
    }
    return demander(nb_personnages);
}

void choisir_equipe(Personnage personnages[], int nb_personnages, Equipe equipe[]) {
    /*
        * La fonction choisir_equipe() permet à l'utilisateur de choisir une équipe de personnages.
        * Elle prend en paramètre un tableau de Personnage, le nombre de personnages disponibles et un pointeur vers une structure Equipe.
        * Si le nombre de personnages est inférieur ou égal à 0, elle affiche un message d'erreur et quitte le programme.
        * Sinon, elle demande à l'utilisateur de choisir un nom pour son équipe et sélectionne les membres de l'équipe.
    */
    if (nb_personnages <= 0) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
        exit(1);
    }
    printf(
        "\n"
        "\n\033[1;33m"
        "\033[38;5;81m"
        "\033[3m"
        "Quel sera le nom de votre equipe ? "
        "\033[0m"
    );

    char tmp[MAX_CARACTERES];
    scanf("%s", tmp);

    int n = strlen(tmp);
    if (n > MAX_CARACTERES) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
        exit(1);
    }

    (*equipe).nom = malloc(sizeof(char) * (n + 1));
    strcpy((*equipe).nom, tmp);

    while (getchar() != '\n');

    int indices_selectionnes[MAX_MEMBRES] = {-1, -1, -1};
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf(
            "\n\033[1;40m"
            "~ %d sur %d"
            "\033[0m", i + 1, MAX_MEMBRES
        );
        int index_personnage = choisir_personnage(nb_personnages);

        int deja_selectionne = 0;
        for (int j = 0; j < i; j++) {
            if (indices_selectionnes[j] == index_personnage) {
                deja_selectionne = 1;
                break;
            }
        }

        if (deja_selectionne == 1) {
            printf(
                "\033[1;31m"
                "%s est deja sous vos ordres."
                "\033[0m\n", personnages[index_personnage].nom
            );
            i--;
        } else {
            indices_selectionnes[i] = index_personnage;
            (*equipe).membres[i] = personnages[index_personnage];
            (*equipe).nb_membres++;
            printf(
                "\033[1;39m"
                "%s pret au combat."
                "\n\033[0m", personnages[index_personnage].nom
            );
        }
    }

    printf("\nAinsi, ");
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf("\033[1;39m%s, \033[0m", (*equipe).membres[i].nom);
    }
    printf("sont vos guerriers.\n\n");
}

void equipe_aleatoire(Personnage personnages[], int nb_personnages, Equipe equipe[]) {
    /*
        * La fonction equipe_aleatoire() génère une équipe de personnages aléatoires.
        * Elle prend en paramètre un tableau de Personnage, le nombre de personnages disponibles et un pointeur vers une structure Equipe.
        * Si le nombre de personnages est inférieur à 3, elle affiche un message d'erreur et quitte le programme.
        * Sinon, elle sélectionne aléatoirement 3 membres pour l'équipe.
    */
    if (nb_personnages < MAX_MEMBRES) {
        printf(
            "\033[1;31m"
            "Erreur : Parametres hors de portee."
            "\n\033[0m"
        );
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
    /*
        * La fonction afficher_equipe() affiche les équipes de joueurs et d'ennemis.
        * Elle prend en paramètre deux structures Equipe.
        * Elle affiche le nom de chaque équipe ainsi que les membres de chaque équipe.
    */
    attendre(2);
    nettoyer();

    discours();
    printf(
        "\033[1;40m"
        "\"%s, %s, %s "
        "\033[1;1m"
        "~ contre ~"
        "\033[0m"
        "\033[1;40m"
        " %s, %s, %s\""
        "\n\033[0m\n", 
           equipe_joueur[0].membres[0].nom, 
           equipe_joueur[0].membres[1].nom, 
           equipe_joueur[0].membres[2].nom,
           equipe_ennemi[0].membres[0].nom, 
           equipe_ennemi[0].membres[1].nom, 
           equipe_ennemi[0].membres[2].nom);

}

void mode_univers(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_univers[]) {
    /*
        * La fonction mode_univers() gère le mode de jeu "univers".
        * Elle prend en paramètre un tableau de Personnage, une structure Equipe pour le joueur et une structure Equipe pour l'univers.
        * Elle permet au joueur de choisir son équipe et génère aléatoirement l'équipe de l'univers.
        * Ensuite, elle affiche les équipes et demande à l'utilisateur de choisir la difficulté de l'univers.
    */
    printf(
        "\n\033[1;40m"
        "Formez votre equipe."
        "\033[0m"

    );
    choisir_equipe(entites, MAX_PERSONNAGES, &equipe_joueur[0]);
    printf(
        "\033[1;37m"
        "Choisissez la difficulte de l'adversaire :\n"
        "   0 ~ Debutant\n"
        "   1 ~ Facile\n"
        "   2 ~ Normal\n"
        "\033[0m"
    );
    int difficulte = demander(3);
    chaudron();
        printf(
        "\033[1;40m"
        "L'univers forme son equipe."
        "\033[0m\n"
    );
    equipe_aleatoire(entites, MAX_MEMBRES, equipe_univers);

    afficher_equipe(equipe_joueur, equipe_univers);

    joueur_vs_univers(&equipe_joueur[0], equipe_joueur[0].membres, MAX_MEMBRES, equipe_univers[0].membres, MAX_MEMBRES, difficulte);
}

void mode_versus(Personnage entites[], Equipe equipe1[], Equipe equipe2[]) {
    /*
        * La fonction mode_versus() gère le mode de jeu "versus".
        * Elle prend en paramètre un tableau de Personnage et deux structures Equipe pour les deux équipes.
        * Elle permet à chaque joueur de choisir son équipe et affiche les équipes.
    */
    printf(
        "\n\033[1;39m"
        "Formez l'equipe 1."
        "\033[0m"
    );
    choisir_equipe(entites, MAX_PERSONNAGES, &equipe1[0]);

    printf(
        "\n\033[1;39m"
        "Formez l'equipe 2."
        "\033[0m"
    );
    choisir_equipe(entites, MAX_PERSONNAGES, &equipe2[0]);

    afficher_equipe(equipe1, equipe2);

    joueur_vs_joueur(&equipe1[0], equipe1[0].membres, MAX_MEMBRES,
                    &equipe2[0], equipe2[0].membres, MAX_MEMBRES);
}

void charger(Personnage entites[], Equipe equipe_joueur[], Equipe equipe_ennemi[], int mode) {
    /*
    La fonction charger() charge les personnages et les équipes à partir d'un fichier.
    Elle prend en paramètre un tableau de Personnage, deux structures Equipe pour le joueur et l'ennemi, et un mode de jeu.
    Elle affiche les personnages disponibles et demande à l'utilisateur de choisir son équipe.
    Ensuite, elle génère aléatoirement l'équipe ennemie et affiche les équipes.
    */
    nettoyer();
    int nb_personnages = afficher_personnages(entites, MAX_PERSONNAGES);

    if (mode == 0) {
        mode_univers(entites, equipe_joueur, equipe_ennemi);
    } else if (mode == 1) {
        mode_versus(entites, equipe_joueur, equipe_ennemi);
    }
    
    printf("\n");
}
