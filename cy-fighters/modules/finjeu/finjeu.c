#include "finjeu.h"
#include <stdlib.h>

void liberation_de_memoire(Personnage personnages[], Equipe equipe[], Equipe equipe_ennemie[]) {
    /*
    La fonction liberation_de_memoire() libère la mémoire allouée pour les personnages et les équipes.
    Elle prend en paramètre un tableau de Personnage, une structure Equipe et une structure Equipe ennemie.
    Elle vérifie si les pointeurs sont valides, puis libère la mémoire allouée pour les noms des équipes.
    */
    if (equipe != NULL && equipe->nom != NULL) {
        free(equipe->nom);
    }
    if (equipe_ennemie != NULL && equipe_ennemie->nom != NULL) {
        free(equipe_ennemie->nom);
    }
}