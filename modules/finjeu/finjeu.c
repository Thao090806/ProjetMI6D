#include "finjeu.h"
#include <stdlib.h>

void liberation_de_memoire(Personnage personnages[], Equipe equipe[], Equipe equipe_ennemie[]) {
    if (personnages == NULL || equipe == NULL || equipe_ennemie == NULL) {
        printf("\033[1;31mErreur : personnages, equipe ou equipe ennemie invalide.\033[0m\n");
        return;
    }
    free(personnages);
    free(equipe);
    free(equipe_ennemie);
}