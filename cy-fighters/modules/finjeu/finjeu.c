#include "finjeu.h"
#include <stdlib.h>

void fin_jeu(Personnage personnages[], Equipe equipe[], Equipe equipe_ennemie[]) {
    free(personnages);
    free(equipe);
    free(equipe_ennemie);
}