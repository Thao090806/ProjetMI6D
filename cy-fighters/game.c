#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "src/initialization.o"
#include "src/script.o"
#include "src/logic.o"
#include "src/fight.o"
#include "src/endgame.o"

int main(){

    Fighters entity[MAX_ENTITYS]; 
    Teams entity_team[MAX_MEMBRES]; 
    Teams enemy_team[MAX_MEMBRES]; 

    inisialization(entity);

    story();
    mode();
    ask(3);

    load(entity, entity_team, enemy_team);

    endgame(entity, entity_team, enemy_team);

    printf("\n");
  
    return 0;
}