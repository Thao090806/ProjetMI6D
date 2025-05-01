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

    fighters[0] = init_fighter("Le Sans-eclat", "Un guerrier errant, porteur d'un destin incertain, mais d'une volonte inebranlable", 8, 7, 7, 6, 6);
    fighters[1] = init_fighter("Malenia", "Une epeiste legendaire, incarnation de la grace et de la mort, redoutable mais fragile", 6, 9, 5, 10, 8);
    fighters[2] = init_fighter("Godfrey", "Un guerrier imposant, incarnation de la force brute et de la determination", 10, 9, 8, 5, 4);
    fighters[3] = init_fighter("Ranni", "Une sorciere enigmatique, gardienne des secrets des astres et des ombres", 5, 10, 4, 7, 5);
    fighters[4] = init_fighter("Mohg", "Un prince maudit, maitre des flammes sanglantes et des rituels interdits", 9, 8, 6, 6, 5);
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

void select_team(Fighters fighters[], int nb_fighters, Teams *team) {
    /*
        Permet au joueur de sélectionner une équipe de 3 personnages parmi les 6 disponibles.
    */
    printf("--- Sélection de l'équipe ---\n");
    printf("Entrez le nom de votre équipe : ");
    scanf("%s", (*team).nom); // Lecture du nom de l'équipe
    printf("Le nom de votre equipe est : %s\n", (*team).nom);

    int selected_indices[MAX_MEMBRES] = {-1, -1, -1}; // Stocke les indices des personnages sélectionnés
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf("\nChoisissez le personnage %d/%d pour votre équipe :\n", i + 1, MAX_MEMBRES);
        int fighter_index = select_fighter(fighters, nb_fighters);

        // Vérifier si le personnage est déjà sélectionné
        int selected = 0;
        for (int j = 0; j < i; j++) {
            if (selected_indices[j] == fighter_index) {
                selected = 1;
                break;
            }
        }

        if (selected == 1) {
            printf("Ce personnage est déjà dans votre équipe. Veuillez en choisir un autre.\n");
            i--; // Refaire la sélection pour ce tour
        } else {
            selected_indices[i] = fighter_index;
            (*team).fighters[i] = fighters[fighter_index]; // Ajouter le personnage à l'équipe
            (*team).nb_membres++; // Incrémenter le nombre de membres de l'équipe
            printf("%s a été ajouté à votre équipe.\n", fighters[fighter_index].nom);
        }
    }

    printf("\nVotre équipe est prête :\n");
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf("- %s\n", (*team).fighters[i].nom);
    }
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

int select_skill(Fighters fighters[], int fighter_index) {
    /*
        Sélectionne une compétence parmi les compétences du personnage sélectionné.
        Renvoie l'index de la compétence sélectionnée.
    */
    int choix = -1; // Initialisation de choix à une valeur invalide

    while (1) { // Boucle infinie pour gérer les entrées invalides
        printf("Choisissez votre competence (0-%d) : ", fighters[fighter_index].nb_skills - 1);
        if (scanf("%d", &choix) == 1 && choix >= 0 && choix < fighters[fighter_index].nb_skills) {
            break;
        } else {
            printf("Choix invalide. Veuillez entrer un nombre entre 0 et %d.\n", fighters[fighter_index].nb_skills - 1);
            while (getchar() != '\n'); // Nettoyer le buffer d'entrée
        }
    }

    printf("Vous avez choisi la competence %s !\n", fighters[fighter_index].skills[choix].nom);
    return choix; // Retourne l'index de la compétence sélectionnée
}

void attack_target(Fighters *attacker, Fighters *target, int skill_index) {
    /*
        Effectue une attaque d'un personnage sur un autre.
        Calcule les dégâts infligés en fonction de l'attaque et de la défense.
    */
    int degats = (*attacker).skills[skill_index].coefficient - (*target).defense; // Calcul des dégâts
    if (degats < 0) {
        degats = 0; // Les dégâts ne peuvent pas être négatifs
    }
    (*target).pv_courant -= degats; // Réduction des points de vie de la cible
    printf("%s attaque %s avec %s et inflige %d degats !\n", (*attacker).nom, (*target).nom, (*attacker).skills[skill_index].nom, degats);
}

    
void game() {
    /*
        Fonction principale du jeu.
        Initialise les personnages et l'équipe, 
        affiche les personnages disponibles, 
        et permet au joueur de sélectionner un personnage.
    */
    Fighters fighters[MAX_FIGHTERS]; // Allocation d'un tableau de personnages
    Teams player_team; // Création d'une équipe pour le joueur
    Teams enemy_team; // Création d'une équipe pour l'ennemi 
    init_fighters(fighters); // Initialisation des personnages
    init_skills(fighters);  // Initialisation des compétences

    printf("---Debut du jeu---\n");
    printf("Bienvenue dans CY-FIGHTERS !\n");

    show_fighters(fighters, MAX_FIGHTERS); // Affichage des personnages disponibles
    // Sélection de l'équipe du joueur
    select_team(fighters, MAX_FIGHTERS, &player_team);

    // Création de l'équipe adverse (prédéfinie ou aléatoire)
    strcpy(enemy_team.nom, "Adversaires");
    for (int i = 0; i < MAX_MEMBRES; i++) {
        enemy_team.fighters[i] = fighters[(i + 3) % MAX_FIGHTERS]; // Exemple : sélection des 3 derniers personnages
    }
    printf("\nL'équipe adverse est composée de :\n");
    for (int i = 0; i < MAX_MEMBRES; i++) {
        printf("- %s\n", enemy_team.fighters[i].nom);
    }
    // Boucle principale du jeu
    int turn = 0; // 0 pour le joueur, 1 pour l'équipe adverse
    while (1) {
        printf("\n--- Tour %s ---\n", turn == 0 ? "du joueur" : "de l'équipe adverse");

        if (turn == 0) {
            // Tour du joueur
            printf("Choisissez un personnage de votre équipe pour attaquer :\n");
            int player_index = select_fighter(player_team.fighters, MAX_MEMBRES);
            Fighters *player = &player_team.fighters[player_index];

            // Sélection de la compétence
            int skill_index = select_skill(player_team.fighters, player_index);

            // Sélection de la cible
            printf("\nChoisissez une cible parmi l'équipe adverse :\n");
            int target_index = select_fighter(enemy_team.fighters, MAX_MEMBRES);
            Fighters *target = &enemy_team.fighters[target_index];

            // Effectuer l'attaque
            attack_target(player, target, skill_index);
        } 
        else {
            // Tour de l'équipe adverse
            int enemy_index = rand() % MAX_MEMBRES; // Sélection aléatoire d'un personnage
            Fighters *enemy = &enemy_team.fighters[enemy_index];

            // Sélection aléatoire d'une compétence
            int skill_index = rand() % enemy->nb_skills;

            // Sélection aléatoire d'une cible
            int target_index = rand() % MAX_MEMBRES;
            Fighters *target = &player_team.fighters[target_index];

            // Effectuer l'attaque
            attack_target(enemy, target, skill_index);
    
    }
    // Changer de tour
    turn = 1 - turn;
}



#endif