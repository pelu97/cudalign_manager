#include <stdlib.h>
#include "base.h"

int VerboseMode = 0;

char CurrentGpu[200];

void clearTerminal(){
    #ifndef DISABLE_CLEAR
    system("clear");
    #endif
}

void toggleVerboseMode(){
    VerboseMode = !VerboseMode;
}
