#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h> // Windows
#else
    #include <unistd.h>  // Linux/macOS
#endif

#include "src/initialization.o"
#include "src/script.o"
#include "src/logic.o"
#include "src/fight.o"
#include "src/endgame.o"

int main(){

    Fighters entity[MAX_ENTITYS]; 
    Teams entity_team[MAX_MEMBRES]; 
    Teams enemy_team[MAX_MEMBRES]; 

    srand(time(NULL)); 

    clean();
    
    wizard();
    inisialization(entity);
    printf("\n");
    wait(5);

    clean();


    story();
    mode();

    load(entity, entity_team, enemy_team, ask(3));

    endgame(entity, entity_team, enemy_team);

    printf("\n");
  
    return 0;
}