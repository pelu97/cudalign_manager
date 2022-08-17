#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameter.h"
#include "base.h"



t_parameter* BestParameters = NULL;

int SimpleProfile = 0;
int CompleteProfile = 0;

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
    char buffer[4000], gpu[1000];
    int size, blocks, threads, simple, complete, found;

    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Current Gpu: %s\n", CurrentGpu);
    #endif

    fp = fopen(PARAM_FILE, "r");

    if(fp == NULL){
        BestParameters = NULL;
    }
    else{
        // needs to compare the gpu found in the file to the gpu in the machine, until finding the corresponding gpu in the file

        // fscanf(fp, "#%s\n", buffer);
        // fgets(buffer, 4000, fp);
        // printf("GPU %s\n", buffer);

        found = 0;

        while((!found) && (fgets(buffer, 4000, fp) != NULL)){
            // fgets(buffer, 4000, fp);

            if(buffer[0] == '#'){
                sscanf(buffer, "#%4000[^#]# simple:%d complete:%d\n", gpu, &simple, &complete);

                #ifdef DEBUG
                printf("[DEBUG - PARAMETER] Comparing CurrentGpu - GPU [%s - %s]\n", CurrentGpu, gpu);
                #endif
                if(!strcmp(gpu, CurrentGpu)){
                    found = 1;
                }
            }
        }

        // Found the gpu in the file, read parameters for it
        if(found){
            #ifdef DEBUG
            printf("[DEBUG - PARAMETER] GPU: %s, simple: %d, complete: %d\n", gpu, simple, complete);
            #endif

            SimpleProfile = simple;
            CompleteProfile = complete;

            while((fgets(buffer, 4000, fp) != NULL)){
                if(buffer[0] == '-'){
                    sscanf(buffer, "--size:%d threads:%d blocks:%d\n", &size, &threads, &blocks);
                    addParameter(size, threads, blocks);
                }
                else{
                    break;
                }
                // #ifdef DEBUG
                // printf("[DEBUG - PARAMETER] Loaded parameter: size:%d threads:%d blocks:%d\n", size, threads, blocks);
                // #endif
            }

            // while(fscanf(fp, "--size:%d threads:%d blocks:%d\n", &size, &threads, &blocks) != EOF){
            //     addParameter(size, threads, blocks);
            //     // #ifdef DEBUG
            //     // printf("[DEBUG - PARAMETER] Loaded parameter: size:%d threads:%d blocks:%d\n", size, threads, blocks);
            //     // #endif
            // }
        }

        // fscanf(fp, "#%4000[^#]# simple:%d complete:%d\n", buffer, &simple, &complete);
        // printf("Gpu: %s, simple: %d, complete: %d\n", buffer, simple, complete);

        // SimpleProfile = simple;
        // CompleteProfile = complete;


        // fscanf(fp, "--size:%d threads:%d blocks:%d\n", &size, &threads, &blocks);
        // printf("Read %d %d %d\n", size, threads, blocks);

        fclose(fp);
    }
}


void insertLine(char* newLine, FILE *fp, long int insertPosition){
    char **buffers = NULL;
    int i=0, bufferLimit;

    // Similar to overwriteLine, but saves the line that would be overwritten to be written back right after the line that will be inserted.
    // fp will be moved back to the insertPosition, so the line that would be overwritten is also saved


    buffers = realloc(buffers, sizeof(char*) * (i+1));
    buffers[0] = malloc(50);

    // seeks back to the insertPosition
    fseek(fp, insertPosition, SEEK_SET);

    // reads every line from file after and including the insertPosition and store in an array of buffers
    while(fgets(buffers[i], 50, fp) != NULL){
        i++;
        buffers = realloc(buffers, sizeof(char*) * (i+1));
        buffers[i] = malloc(50);
    }

    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Read and stored %d lines from file to be shifted\n", i);
    #endif

    // seeks back to the insertPosition
    fseek(fp, insertPosition, SEEK_SET);

    // overwrites the line, but the line located here was saved to a buffer
    fputs(newLine, fp);

    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Inserted line in position %ld with (%s)\n", insertPosition, newLine);
    #endif

    bufferLimit = i;

    for(i=0; i<bufferLimit; i++){
        fputs(buffers[i], fp);
        free(buffers[i]);
    }

    free(buffers[i]);
    free(buffers);


    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Written back %d lines to file\n", i);
    #endif
}


void overwriteLine(char* newLine, FILE *fp, long int overwritePosition){
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
    printf("[DEBUG - PARAMETER] Overwrote line in position %ld with (%s)\n", overwritePosition, newLine);
    #endif

    bufferLimit = i;

    for(i=0; i<bufferLimit; i++){
        fputs(buffers[i], fp);
        free(buffers[i]);
    }

    free(buffers[i]);
    free(buffers);


    #ifdef DEBUG
    printf("[DEBUG - PARAMETER] Written back %d lines to file\n", i);
    #endif
}


void saveParameters(int size, int threads, int blocks){
    FILE *fp;
    int sizeRead, threadsRead, blocksRead, found=0, foundGpu, sectionEnded, simple, complete;
    long int position, positionHelper;
    char newLine[1200], buffer[1200], gpu[1000];

    fp = fopen(PARAM_FILE, "r+");

    if(fp == NULL){
        // parameter file doesn't exist yet, create new one
        fp = fopen(PARAM_FILE, "w");
        fprintf(fp, "#%s# simple:%d complete:%d\n", CurrentGpu, SimpleProfile, CompleteProfile);
        fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);
        #ifdef DEBUG
        printf("[DEBUG - PARAMETER] - Didn't find parameter file, created new one\n");
        printf("[DEBUG - PARAMETER] - Added best parameters to file (size:%d threads:%d blocks:%d)\n", size, threads, blocks);
        #endif
        fclose(fp);
    }
    else{
        // looks for the gpu in the parameter file

        foundGpu = 0;

        position = ftell(fp);
        while((!foundGpu) && (fgets(buffer, 4000, fp) != NULL)){
            // fgets(buffer, 4000, fp);
            if(buffer[0] == '#'){
                sscanf(buffer, "#%4000[^#]# simple:%d complete:%d\n", gpu, &simple, &complete);

                #ifdef DEBUG
                printf("[DEBUG - PARAMETER] Comparing CurrentGpu - GPU [%s - %s]\n", CurrentGpu, gpu);
                #endif
                if(!strcmp(gpu, CurrentGpu)){
                    foundGpu = 1;
                }
            }
            // if gpu already found, hold its position
            if(!foundGpu){
                position = ftell(fp);
            }
        }

        if(foundGpu){
            // found a section for the current gpu in the file
            // overwrite the gpu header line updating the simple or complete profile flags

            sprintf(newLine, "#%s# simple:%d complete:%d\n", gpu, SimpleProfile, CompleteProfile);

            // gets current position (line right after the gpu header)
            positionHelper = ftell(fp);

            overwriteLine(newLine, fp, position);

            // seeks back to the line after the gpu header
            fseek(fp, positionHelper, SEEK_SET);

            found = 0;
            sectionEnded = 0;
            // Find a line with the same size in the file to update best parameters
            position = ftell(fp);
            while((fgets(buffer, 4000, fp) != NULL)){
                #ifdef DEBUG
                printf("[DEBUG - PARAMETER] - Looking for matching line in file in position %ld\n", position);
                #endif

                if(buffer[0] == '-'){
                    sscanf(buffer, "--size:%d threads:%d blocks:%d\n", &sizeRead, &threadsRead, &blocksRead);

                    if(sizeRead == size){
                        found = 1;

                        sprintf(newLine, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

                        overwriteLine(newLine, fp, position);

                        #ifdef DEBUG
                        printf("[DEBUG - PARAMETER] - Found matching line in file (position %ld). Overwrote best parameters to file (size:%d threads:%d blocks:%d)\n", position, size, threads, blocks);
                        #endif

                        break;
                    }
                }
                else if(buffer[0] == '#'){
                    // found another gpu already
                    found = 0;
                    sectionEnded = 1;

                    sprintf(newLine, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

                    insertLine(newLine, fp, position);

                    #ifdef DEBUG
                    printf("[DEBUG - PARAMETER] - GPU section ended (position %ld). Inserting new line here\n", position);
                    #endif

                    break;
                }
                position = ftell(fp);
            }


            // while(fscanf(fp, "--size:%d threads:%d blocks:%d\n", &sizeRead, &threadsRead, &blocksRead) != EOF){
            //     #ifdef DEBUG
            //     printf("[DEBUG - PARAMETER] - Looking for matching line in file in position %ld\n", position);
            //     #endif
            //
            //     if(sizeRead == size){
            //         found = 1;
            //
            //         sprintf(newLine, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);
            //
            //         overwriteLine(newLine, fp, position);
            //
            //         // fseek(fp, position, SEEK_SET);
            //
            //         // fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);
            //
            //         #ifdef DEBUG
            //         printf("[DEBUG - PARAMETER] - Found matching line in file (position %ld). Overwrote best parameters to file (size:%d threads:%d blocks:%d)\n", position, size, threads, blocks);
            //         #endif
            //
            //         break;
            //     }
            //     position = ftell(fp);
            // }

            if((!found) && (!sectionEnded)){
                // Didn't find line to overwrite and gpu section didn't end, meaning the file has ended, add a new one to the end of the file
                fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

                #ifdef DEBUG
                printf("[DEBUG - PARAMETER] - No matching line in file. Added best parameters to file (size:%d threads:%d blocks:%d)\n", size, threads, blocks);
                #endif
            }
        }
        else{
            // didn't find a section for the current gpu in the file, create one
            fprintf(fp, "#%s# simple:%d complete:%d\n", CurrentGpu, SimpleProfile, CompleteProfile);
            fprintf(fp, "--size:%d threads:%d blocks:%d\n", size, threads, blocks);

            #ifdef DEBUG
            printf("[DEBUG - PARAMETER] - No matching gpu section in file. Added GPU section and best parameters to file (size:%d threads:%d blocks:%d)\n", size, threads, blocks);
            #endif
        }


    }

    fclose(fp);


}


void freeParameterTable(){
    t_parameter *parameter, *temp;

    parameter = BestParameters;

    while(parameter != NULL){
        temp = parameter;
        parameter = parameter->next;
        free(temp);
    }
}


void printParamaterTable(){
    t_parameter *temp;

    temp = BestParameters;

    while(temp != NULL){
        printf("Size: %d - Threads: %d - Blocks: %d\n", temp->size, temp->threads, temp->blocks);

        temp = temp->next;
    }
}
