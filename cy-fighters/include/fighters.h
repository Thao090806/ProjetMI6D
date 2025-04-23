#include


typedef struct {
    char nom[30];
    float hp_coutant;
    int hp_max;
    int atk;
    int dfs;
    int agilite;
    int speed;
    Techniques techniques
}Fighters;


typedef struct{
    char nom[30];
    int valeur;
    char description[100];
    int tours_actifs;
    int tours_recharges;
}Techniques;

typedef struct {
   char nom[30];
   int nb_combattants;
   Fighters fighters; 
}Equipe;
