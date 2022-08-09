#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"
#include "base.h"



t_parameter* BestParameters = NULL;


void addParameter(int size, int threads, int blocks){
    t_parameter* newParameter, *temp;

    newParameter = malloc(sizeof(t_parameter));

    newParameter->size = size;
    newParameter->threads = threads;
    newParameter->blocks = blocks;
    newParameter->next = NULL;

    if(BestParameters == NULL){
        BestParameters = newParameter;
    }
    else{
        temp = BestParameters;

        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = newParameter;
    }

    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] - Added parameters [blocks: %d, threads: %d] for sequence of size %d to memory\n", blocks, threads, size);
    #endif

}


void loadParameters(){
    FILE *fp;
    char buffer[4000];
    int size, blocks, threads;

    fp = fopen(PARAM_FILE, "r");

    if(fp == NULL){
        BestParameters = NULL;
    }
    else{
        // fscanf(fp, "#%s\n", buffer);
        // fgets(buffer, 4000, fp);
        // printf("GPU %s\n", buffer);

        // fscanf(fp, "--size:%d threads:%d blocks:%d\n", &size, &threads, &blocks);
        // printf("Read %d %d %d\n", size, threads, blocks);
        while(fscanf(fp, "--size:%d threads:%d blocks:%d\n", &size, &threads, &blocks) != EOF){
            addParameter(size, threads, blocks);
        }
    }
}


void overwriteLine(char* newLine, FILE *fp, int overwritePosition){
    char **buffers = NULL;
    int i=0, bufferLimit;

    // Saves all the lines after the one marked to overwrite in buffers, than overwrite the line and rewrites back the lines from the buffers
    // fp must be in the position after the line to be overwritten already

    buffers = realloc(buffers, sizeof(char*) * (i+1));
    buffers[0] = malloc(50);

    // reads every line from file after the overwritePosition and store in an array of buffers
    while(fgets(buffers[i], 50, fp) != NULL){
        i++;
        buffers = realloc(buffers, sizeof(char*) * (i+1));
        buffers[i] = malloc(50);
    }

    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Read and stored %d lines from file to be shifted\n", i);
    #endif

    // seeks back to the overwritePosition
    fseek(fp, overwritePosition, SEEK_SET);

    // overwrites the line
    fputs(newLine, fp);

    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Overwrote line in position %d with (%s)\n", overwritePosition, newLine);
    #endif

    bufferLimit = i;

    for(i=0; i<bufferLimit; i++){
        fputs(buffers[i], fp);
    }


    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Written back %d lines to file\n", i);
    #endif
}


void saveParameters(int size, int threads, int blocks){
    FILE *fp;
    int sizeRead, threadsRead, blocksRead, found=0;
    long int position;
    char newLine[50];

    fp = fopen(PARAM_FILE, "r+");

    if(fp == NULL){
        // parameter file doesn't exist yet, create new one
        fp = fopen(PARAM_FILE, "w");
        fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);
        #ifdef DEBUG
        printf("[DEBUG - PARAMETER] - Didn't find parameter file, created new one\n");
        printf("[DEBUG - PARAMETER] - Added best parameters to file (size:%d threads:%d blocks:%d)\n", size, threads, blocks);
        #endif
    }
    else{
        // Find a line with the same size in the file to update best parameters
        position = ftell(fp);
        while(fscanf(fp, "--size:%d threads:%d blocks:%d\n", &sizeRead, &threadsRead, &blocksRead) != EOF){
            #ifdef DEBUG
            printf("[DEBUG - PARAMETER] - Looking for matching line in file in position %d\n", position);
            #endif

            if(sizeRead == size){
                found = 1;

                sprintf(newLine, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

                overwriteLine(newLine, fp, position);

                // fseek(fp, position, SEEK_SET);

                // fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

                #ifdef DEBUG
                printf("[DEBUG - PARAMETER] - Found matching line in file (position %d). Overwrote best parameters to file (size:%d threads:%d blocks:%d)\n", position, size, threads, blocks);
                #endif

                break;
            }
            position = ftell(fp);
        }

        if(!found){
            // Didn't find line to overwrite, add a new one to the end of the file
            fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

            #ifdef DEBUG
            printf("[DEBUG - PARAMETER] - No matching line in file. Added best parameters to file (size:%d threads:%d blocks:%d)\n", size, threads, blocks);
            #endif
        }
    }

    fclose(fp);


}


void printParamaterTable(){
    t_parameter *temp;

    temp = BestParameters;

    while(temp != NULL){
        printf("Size: %d - Threads: %d - Blocks: %d\n", temp->size, temp->threads, temp->blocks);

        temp = temp->next;
    }
}
