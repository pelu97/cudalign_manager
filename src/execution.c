#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "execution.h"
#include "parser.h"
#include "parameter.h"
#include "cleanup.h"

t_execution* ExeList = NULL;
int currentThreads = -1;

void insertExeList(char* seqA, char* seqB, int size, int threads, int blocks, int bp, int isProfile){
    t_execution *newElement, *temp;

    newElement = malloc(sizeof(t_execution));

    strcpy(newElement->seqA, seqA);
    strcpy(newElement->seqB, seqB);

    newElement->seqA_ID[0] = '\0';
    newElement->seqB_ID[0] = '\0';

    newElement->size = size;
    newElement->threads = threads;
    newElement->blocks = blocks;
    newElement->bp = bp;
    newElement->isProfile = isProfile;
    newElement->time = -1;
    newElement->mcups = -1;
    newElement->next = NULL;

    if(ExeList == NULL){
        ExeList = newElement;
    }
    else{
        temp = ExeList;
        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = newElement;
    }

    #ifdef DEBUG
    printf("[DEBUG - EXECUTION] - Inserted execution into execution list (%dM %d %dT %dB)\n", size, bp, blocks, threads);
    #endif

}


void setExeSize(t_execution* execution, int size){

    if(execution != NULL){
        if(execution->size != -1){
            #ifdef DEBUG
            printf("[DEBUG - EXECUTION] - Overwriting execution size from %d to %d\n", execution->size, size);
            #endif
        }
        size = size/1000000;
        if(size < 1){
            size = 1;
        }

        execution->size = size;
    }

}


void printExeList(){
    t_execution *temp;
    int i;

    if(ExeList == NULL){
        printf("Empty list.\n");
    }
    else{
        temp = ExeList;
        i=1;
        while(temp != NULL){
            printf("List element %d: SeqA=%s, SeqB=%s, Size=%d, Threads=%d, Blocks=%d, BP=%d\n", i, temp->seqA, temp->seqB, temp->size, temp->threads, temp->blocks, temp->bp);
            i++;
            temp = temp->next;
        }
    }
}

void inputExeList(){
    int executions, i, size, threads, blocks, bp;

    printf("How many executions?\n");
    scanf("%d", &executions);
    printf("%d executions\n", executions);

    for(i=0; i<executions; i++){
        printf("-Execution %d\n", i+1);
        printf("--Size: ");
        scanf("%d", &size);
        printf("--Threads: ");
        scanf("%d", &threads);
        printf("--Blocks: ");
        scanf("%d", &blocks);
        printf("--BP: ");
        scanf("%d", &bp);

        insertExeList("seqA", "seqB", size, threads, blocks, bp, 0);
    }

    printExeList();
}

void runExeList(){
    t_execution* execution;
    int i, paramsReturn[2];
    char exeLine[1000], seqA[300], seqB[300], cudalignDir[300];

    execution = ExeList;

    checkFiles();

    if(execution == NULL){
        printf("No executions in list.\n");
    }
    else{
        i=1;
        updateExeFile();

        while(execution != NULL){
            // Checks if parameters are already set for the current execution. If not, gets them from the table of best parameters
            if((execution->threads == -1) || (execution->blocks == -1)){
                getBestParam(paramsReturn, execution->size);

                if(execution->threads == -1){
                    execution->threads = paramsReturn[0];
                }
                if(execution->blocks == -1){
                    execution->blocks = paramsReturn[1];
                }
            }


            // Checks the number of threads configured for the current execution

        	if((execution->threads == 64) && (currentThreads != 64)){
        		// Change directory to 64 threads compiled cudalign
        		printf("Using CUDAlign 64 threads directory - "CUDA64_DIR"\n");
        		sprintf(cudalignDir, CUDA64_DIR);
        		//printf("cd "CUDA64_DIR);
        		//system("cd "CUDA64_DIR);
        		currentThreads = 64;
        	}
        	else if((execution->threads == 128) && (currentThreads != 128)){
        		// Change directory to 128 threads compiled cudalign
        		printf("Using CUDAlign 128 threads directory - "CUDA128_DIR"\n");
        		sprintf(cudalignDir, CUDA128_DIR);
        		//printf("cd "CUDA128_DIR);
        		//system("cd "CUDA128_DIR);
        		currentThreads = 128;
        	}
        	else if((execution->threads == 256) && (currentThreads != 256)){
        		// Change directory to 256 threads compiled cudalign
        		printf("Using CUDAlign 256 threads directory - "CUDA256_DIR"\n");
        		sprintf(cudalignDir, CUDA256_DIR);
        		//printf("cd "CUDA256_DIR);
        		//system("cd "CUDA256_DIR);
        		currentThreads = 256;
        	}


            // This will be done by the profiler. Select the directory of the sequences selected for the execution.
            // In case of a user alignment, the user will have provided the directory already.
            // In case of a profiling run, the profiler will have provided the directories.

        	//1M
        	// if(execution->size == 1){
        	// 	sprintf(seqA, SEQ_DIR"/1M/"SEQ_1_A);
        	// 	sprintf(seqB, SEQ_DIR"/1M/"SEQ_1_B);
        	// }

            // Format the execution command using the parameters (cudalign directory, sequences directories and number of blocks)
            sprintf(exeLine, "%s/cudalign --ram-size=5G %s %s --blocks=%d", cudalignDir, execution->seqA, execution->seqB, execution->blocks);
            // Execute command


            // execute
            printf("Execution Line %d: %s\n", i, exeLine);
            // system(exeLine);

            // Finished this execution, update its status
            execution->status = 1;

            if(execution->isProfile){
                // If it was a profiler execution, call fetchResult
                fetchResult(execution);
            }
            else{
                // If it was a user execution, call clean up
                // cleanup
                cleanUp(execution);
            }



            // Update execution list file
            // updateExeFile();

            execution = execution->next;
            i++;
        }

    }
}

void fetchResult(t_execution* execution){
    int stats[2];
    // change into temporary work directory

    // No need to use the cudalign directory. Due to how system works, the work.tmp directory will be in the same directory as the project executable
    readStats(stats);


    #ifdef DEBUG
    printf("[DEBUG - EXECUTION] Execution statistics -Time: %d -MCups: %d\n", stats[0], stats[1]);
    #endif

    // printf("-Time: %d\n-MCups: %d\n", stats[0], stats[1]);

    execution->time = stats[0];
    execution->mcups = stats[1];
}


void getBestParam(int* paramsReturn, int size){
    // params[0] is threads, params[1] is blocks - return array
    t_parameter *param, *prevParam;
    int i;

    param = BestParameters;
    prevParam = NULL;
    i=0;

    // use the return value as a flag to check if a good parameter was found in the table
    paramsReturn[0] = -1;

    while(param != NULL){
        // looks until finding the correct size or one bigger. If exact size, get parameters.
        // if size is bigger, look at the previous and find the closest one to choose from
        if(param->size == size){
            // equal - perfect case
            paramsReturn[0] = param->threads;
            paramsReturn[1] = param->blocks;
            #ifdef DEBUG
            printf("[DEBUG - EXECUTION] - Found best parameters for size %d - T%d B%d\n", size, paramsReturn[0], paramsReturn[1]);
            #endif
            break;
        }
        else if(param->size > size){
            // bigger
            if(prevParam == NULL){
                // first parameter in the table is already bigger
                // use that parameter, its the closest one possible
                paramsReturn[0] = param->threads;
                paramsReturn[1] = param->blocks;
                #ifdef DEBUG
                printf("[DEBUG - EXECUTION] - Found closest (first already bigger) best parameters for size %d - T%d B%d\n", size, paramsReturn[0], paramsReturn[1]);
                #endif
                break;
            }
            else{
                // there was a previous parameter in the table with smaller size. Find the closest one (size wise) and use it
                if( abs(size - prevParam->size) < abs(size - param->size)){
                    // closer to the previous one, use that
                    paramsReturn[0] = prevParam->threads;
                    paramsReturn[1] = prevParam->blocks;
                    #ifdef DEBUG
                    printf("[DEBUG - EXECUTION] - Found closest (closest to previous) best parameters for size %d - T%d B%d\n", size, paramsReturn[0], paramsReturn[1]);
                    #endif
                    break;
                }
                else{
                    // closer to the current one, or the same distance, use the current
                    paramsReturn[0] = param->threads;
                    paramsReturn[1] = param->blocks;
                    #ifdef DEBUG
                    printf("[DEBUG - EXECUTION] - Found closest (closest to current or equal) best parameters for size %d - T%d B%d\n", size, paramsReturn[0], paramsReturn[1]);
                    #endif
                    break;
                }
            }
        }
        else{
            // smaller
            prevParam = param;
            param = param->next;
            i++;
        }

    }

    if((i>0) && (paramsReturn[0] == -1)){
        // checked the table and did'nt find a parameter match
        // only possible if size is bigger then all sizes stored in the table
        // use the last size in the table
        if(prevParam != NULL){
            paramsReturn[0] = prevParam->threads;
            paramsReturn[1] = prevParam->blocks;
            #ifdef DEBUG
            printf("[DEBUG - EXECUTION] - Found closest (bigger than all, using last) best parameters for size %d - T%d B%d\n", size, paramsReturn[0], paramsReturn[1]);
            #endif
        }
        else{
            // this shouldn't happen. If i>0 then there should definitely be a parameter stored in prevParam
            // just to avoid errors, use default values in this case and print a message if debug is enabled
            #ifdef DEBUG
            printf("[DEBUG - EXECUTION] - Unexpected error when looking for best parameters for size %d. Using default values\n", size);
            #endif

            paramsReturn[0] = DEFAULT_THREADS;
            paramsReturn[1] = DEFAULT_BLOCKS;
        }
    }

    if(paramsReturn[0] == -1){
        // If still hasn't found the best parameters, use defaults
        paramsReturn[0] = DEFAULT_THREADS;
        paramsReturn[1] = DEFAULT_BLOCKS;
        #ifdef DEBUG
        printf("[DEBUG - EXECUTION] - Best parameters not found for size %d. Using default values\n", size);
        #endif
    }

}

int getFileSize(FILE* fp){
    int size;

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    #ifdef DEBUG
    printf("[DEBUG - EXECUTION] File size: %d\n", size);
    #endif

    return size;
}

void checkFiles(){
    int i = 1, sizeAverage, sizeA, sizeB;
    t_execution* execution;
    FILE* fp;
    char seqIdBuffer[50];

    execution = ExeList;

    if(execution == NULL){
        printf("No executions in list.\n");
    }
    else{
        while(execution != NULL){

            fp = fopen(execution->seqA, "r");
            if(fp != NULL){
                fscanf(fp, ">%s ", seqIdBuffer);
                rewind(fp);
                strcpy(execution->seqA_ID, seqIdBuffer);

                if(execution->size == -1){
                    // Still doesnt have the sequence size (user alignment)
                    sizeA = getFileSize(fp);
                }
                fclose(fp);
            }
            else{
                printf("Error ocurred when trying to access file [%s] in alignment number %d.\n", execution->seqA, i);
                printf("Check if the file name and path are typed correctly and that the file exists in that path.\n");
                break;
            }

            fp = fopen(execution->seqB, "r");
            if(fp != NULL){
                fscanf(fp, ">%s ", seqIdBuffer);
                rewind(fp);
                strcpy(execution->seqB_ID, seqIdBuffer);

                if(execution->size == -1){
                    // Still doesnt have the sequence size (user alignment)
                    sizeB = getFileSize(fp);
                }
                fclose(fp);
            }
            else{
                printf("Error ocurred when trying to access file [%s] in alignment number %d.\n", execution->seqA, i);
                printf("Check if the file name and path are typed correctly and that the file exists in that path.\n");
                break;
            }

            if(execution->size == -1){
                sizeAverage = (sizeA + sizeB)/2;
                setExeSize(execution, sizeAverage);
            }

            i++;
            execution = execution->next;
        }
    }
}


void updateExeFile(){
    FILE *fp;
    t_execution *execution;

    execution = ExeList;
    fp = fopen(EXE_FILE, "w");

    if(fp == NULL){
        #ifdef DEBUG
        printf("[DEBUG - EXECUTION] Unexpected error ocurred when opening execution list file to update\n");
        #endif
    }
    else{
        while(execution != NULL){
            fprintf(fp, "seqA:%s seqB:%s size:%d threads:%d blocks:%d bp:%d isProfile:%d status:%d time:%d mcups:%d\n",
                execution->seqA, execution->seqB, execution->size, execution->threads, execution->blocks, execution->bp,
                execution->isProfile, execution->status, execution->time, execution->mcups
            );

            execution = execution->next;
        }
        fclose(fp);

        #ifdef DEBUG
        printf("[DEBUG - EXECUTION] Updated execution list file\n");
        #endif
    }

}


void testExeList(){

    insertExeList("seqA", "seqB", 1, 256, 512, 1, 0);
    insertExeList("seqA", "seqB", 1, 128, 256, 1, 0);
    //insertExeList(3, 64, 512, 0);
    //insertExeList(23, 128, 128, 0);
    //insertExeList(23, 128, 256, 0);
    //insertExeList(23, 128, 128, 1);
    //insertExeList(23, 128, 256, 1);

    runExeList();

    printExeList();
}
