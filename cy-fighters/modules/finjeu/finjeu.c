#include "finjeu.h"
#include <stdlib.h>

void liberation_de_memoire(Personnage personnages[], Equipe equipe[], Equipe equipe_ennemie[]) {
    // Libération de la mémoire allouée pour les personnages
    if (equipe != NULL && equipe->nom != NULL) {
        free(equipe->nom);
    }
    if (equipe_ennemie != NULL && equipe_ennemie->nom != NULL) {
        free(equipe_ennemie->nom);
    }
}