#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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


void getCurrentGpu(){
    // gets current gpu in the system using nvidia-smi utility
    // uses the first gpu listed in the information returned, even if there are more gpus connected
    char buffer[4000], newGpu[200];
    char *temp;
    FILE *fp;
    int gpuNumber = -1, varParsed;

    system("nvidia-smi -L > ./gpu.txt");

    fp = fopen("./gpu.txt", "r");

    if(fp == NULL){
        printf("An error ocurred when fetching the GPU model. Using default values. (File not found)\n");
        strcpy(CurrentGpu, "NOT FOUND");
    }
    else{
        temp = fgets(buffer, 4000, fp);

        if(temp == NULL){
            printf("An error ocurred when fetching the GPU model. Using default values. (File read error)\n");
            strcpy(CurrentGpu, "NOT FOUND");
        }

        varParsed = sscanf(buffer, "GPU %d: %200[^(]", &gpuNumber, newGpu);

        if(varParsed != 2){
            printf("An error ocurred when fetching the GPU model. Using default values. (File in wrong format/GPU model not in file)\n");
            strcpy(CurrentGpu, "NOT FOUND");
        }
        else{
            strcpy(CurrentGpu, newGpu);
            #ifdef DEBUG
            printf("[DEBUG - BASE] Found gpu model (GPU %d): %s\n", gpuNumber, newGpu);
            #endif
        }

        #ifdef DEBUG
        printf("[DEBUG - BASE] Variables parsed from gpu file: %d\n", varParsed);
        #endif

        fclose(fp);
    }




}
