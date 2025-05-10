#include "finjeu.h"
#include <stdlib.h>

void liberation_de_memoire(Personnage personnages[], Equipe equipe[], Equipe equipe_ennemie[]) {
    free(personnages);
    free(equipe);
    free(equipe_ennemie);
}