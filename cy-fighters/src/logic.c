#ifndef LOGIC_H
#define LOGIC_H

#include "../data/initialisation.h"

/*
    Inclusion indirecte de characters.h.
    characters.h : contient la structure des personnages leurs compétences et les equipes.
 */

 void init_fighters(Fighters fighters[]) {
    /*
        
    */

    // 1. Le Sans-eclat
    fighters[0] = init_fighter("Le Sans-eclat", "Un guerrier errant, porteur d'un destin incertain, mais d'une volonte inebranlable", 8, 7, 7, 6, 6);

    // 2. Malenia, Lame de Miquella
    fighters[1] = init_fighter("Malenia", "Une epeiste legendaire, incarnation de la grace et de la mort, redoutable mais fragile", 6, 9, 5, 10, 8);

    // 3. Godfrey, Premier Seigneur
    fighters[2] = init_fighter("Godfrey", "Un guerrier imposant, incarnation de la force brute et de la determination", 10, 9, 8, 5, 4);

    // 4. Ranni la Sorciere
    fighters[3] = init_fighter("Ranni", "Une sorciere enigmatique, gardienne des secrets des astres et des ombres", 5, 10, 4, 7, 5);

    // 5. Mohg, Seigneur du Sang
    fighters[4] = init_fighter("Mohg", "Un prince maudit, maitre des flammes sanglantes et des rituels interdits", 9, 8, 6, 6, 5);

    // 6. Morgott, Roi des Omen
    fighters[5] = init_fighter("Morgott", "Un roi maudit, dernier rempart d'un royaume dechire par la decadence", 7, 8, 8, 5, 6);
}

void init_skills(Fighters fighters[]) {
    /*
        
    */

    // Competences du Sans-eclat
    fighters[0].skills[0] = init_skill("Coup du vagabond", "Une attaque equilibree, reflet de sa quete solitaire", 40, 1, 2);
    fighters[0].skills[1] = init_skill("Determination", "Une volonte inebranlable qui renforce temporairement l'attaque", 0, 2, 3);
    fighters[0].skills[2] = init_skill("Riposte", "Une contre-attaque precise et decisive", 50, 1, 2);
    fighters[0].nb_skills = 3;

    // Competences de Malenia
    fighters[1].skills[0] = init_skill("Danse de lames", "Une serie d'attaques gracieuses et mortelles", 60, 1, 4);
    fighters[1].skills[1] = init_skill("Regeneration", "Une force mystique qui restaure des points de vie apres chaque attaque", 0, 3, 5);
    fighters[1].skills[2] = init_skill("Lame ecarlate", "Une frappe sanglante qui inflige des degats et applique un saignement", 50, 2, 4);
    fighters[1].nb_skills = 3;

    // Competences de Godfrey
    fighters[2].skills[0] = init_skill("Frappe colossale", "Une attaque devastatrice qui ebranle les ennemis", 70, 1, 3);
    fighters[2].skills[1] = init_skill("Rugissement bestial", "Un cri puissant qui affaiblit les ennemis proches", 0, 2, 4);
    fighters[2].skills[2] = init_skill("Ecrasement terrestre", "Une attaque de zone qui inflige des degats massifs", 80, 1, 5);
    fighters[2].nb_skills = 3;

    // Competences de Ranni
    fighters[3].skills[0] = init_skill("Etoile glaciale", "Une attaque magique qui inflige des degats et ralentit l'ennemi", 50, 1, 3);
    fighters[3].skills[1] = init_skill("Invocation spectrale", "Invoque un allie temporaire", 0, 3, 5);
    fighters[3].skills[2] = init_skill("Pluie d'etoiles", "Une attaque magique de zone", 60, 1, 4);
    fighters[3].nb_skills = 3;

    // Competences de Mohg
    fighters[4].skills[0] = init_skill("Flammes sanglantes", "Une attaque qui inflige des degats et applique un saignement", 60, 1, 3);
    fighters[4].skills[1] = init_skill("Rituel interdit", "Inflige des degats massifs a tous les ennemis au prix de ses propres PV", 90, 1, 5);
    fighters[4].skills[2] = init_skill("Marque du sang", "Affaiblit l'ennemi et reduit sa defense", 0, 2, 4);
    fighters[4].nb_skills = 3;

    // Competences de Morgott
    fighters[5].skills[0] = init_skill("Lame sacree", "Inflige des degats sacres", 70, 1, 3);
    fighters[5].skills[1] = init_skill("Pluie de lames", "Une serie d'attaques rapides", 50, 1, 4);
    fighters[5].skills[2] = init_skill("Jugement divin", "Inflige des degats massifs a tous les ennemis", 90, 1, 5);
    fighters[5].nb_skills = 3;
}

int show_fighters(Fighters fighters[],  int nb_fighter) {
    /*
        Affiche les personnages disponibles pour le joueur.
        Renvoie le nombre de personnages disponibles.
    */
    printf("Personnages disponibles :\n");
    for (int i = 0; i < nb_fighter; i++) {
        printf("> %s - %s\n", fighters[i].nom, fighters[i].description);

        printf("\n  Statistique :\n");
        printf("  - Point de vie : %d/100\n", fighters[i].pv_courant, fighters[i].pv_max);
        printf("  - Attaque : %d/100\n", fighters[i].attaque);
        printf("  - Defense : %d/100\n", fighters[i].defense);
        printf("  - Agilite : %d/100\n", fighters[i].agilite);
        printf("  - Vitesse : %d/100\n", fighters[i].vitesse);

        printf("\n  Competences :\n");
        for(int j = 0; j < fighters[i].nb_skills; j++) { // Affichage des compétences
            printf("  + %s : %s\n   Valeur : %d\n   Tours actifs : %d\n   Tours recharge : %d\n",
                   fighters[i].skills[j].nom,
                   fighters[i].skills[j].description,
                   fighters[i].skills[j].coefficient,
                   fighters[i].skills[j].tours_actifs,
                   fighters[i].skills[j].tours_recharge);
        }

        printf("\n");
    }
    return nb_fighter;
}

int select_fighter(Fighters fighters[], int nb_fighters) {
    /*
    Sélectionne un personnage parmi les personnages disponibles.
    Renvoie l'index du personnage sélectionné.
    */
    int choix = -1; // Initialisation de choix à une valeur invalide

    while (1) { // Boucle infinie pour gérer les entrées invalides
        printf("Choisissez votre personnage (0-%d) : ", nb_fighters - 1);
        if (scanf("%d", &choix) == 1 && choix >= 0 && choix < nb_fighters) {
            // Si l'entrée est valide, on sort de la boucle
            break;
        } else {
            // Si l'entrée est invalide, afficher un message d'erreur
            printf("Choix invalide. Veuillez entrer un nombre entre 0 et %d.\n", nb_fighters - 1);
            while (getchar() != '\n'); // Nettoyer le buffer d'entrée
        }
    }

    printf("Vous avez choisi %s !\n", fighters[choix].nom);
    return choix; // Retourne l'index du personnage sélectionné
}
    
void game() {
    /*
        Fonction principale du jeu.
        Initialise les personnages et l'équipe, 
        affiche les personnages disponibles, 
        et permet au joueur de sélectionner un personnage.
    */
    Fighters fighters[MAX_FIGHTERS]; // Allocation d'un tableau de personnages
    init_fighters(fighters); // Initialisation des personnages
    init_skills(fighters);  // Initialisation des compétences
    show_fighters(fighters, MAX_FIGHTERS); // Affichage des personnages disponibles
    select_fighter(fighters, MAX_FIGHTERS); // Sélection du personnage par le joueur
}



#endif