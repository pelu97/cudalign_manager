#include <stdlib.h>
#include <stdio.h>
#include "execution.h"
#include "parser.h"

t_execution* ExeList = NULL;
int currentThreads = -1;

void insertExeList(int size, int threads, int blocks, int bp){
    t_execution *newElement, *temp;

    newElement = malloc(sizeof(t_execution));

    newElement->size = size;
    newElement->threads = threads;
    newElement->blocks = blocks;
    newElement->bp = bp;
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
    printf("Inserted execution into execution list (%dM %d %dT %dB)\n", size, bp, blocks, threads);
    #endif

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
            printf("List element %d: Size=%d, Threads=%d, Blocks=%d, BP=%d\n", i, temp->size, temp->threads, temp->blocks, temp->bp);
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

        insertExeList(size, threads, blocks, bp);
    }

    printExeList();
}

void runExeList(){
    t_execution* execution;
    int i;
    char exeLine[1000], seqA[300], seqB[300], cudalignDir[300];

    execution = ExeList;

    if(execution == NULL){
        printf("No executions in list.\n");
    }
    else{
        i=1;
        while(execution != NULL){
        
        	if((execution->threads == 64) && (currentThreads != 64)){
        		// Change directory to 64 threads compiled cudalign
        		printf("Changing directory to "CUDA64_DIR"\n");
        		sprintf(cudalignDir, CUDA64_DIR);
        		//printf("cd "CUDA64_DIR);
        		//system("cd "CUDA64_DIR);
        		currentThreads = 64;
        	}
        	else if((execution->threads == 128) && (currentThreads != 128)){
        		// Change directory to 128 threads compiled cudalign
        		printf("Changing directory to "CUDA128_DIR"\n");
        		sprintf(cudalignDir, CUDA128_DIR);
        		//printf("cd "CUDA128_DIR);
        		//system("cd "CUDA128_DIR);
        		currentThreads = 128;
        	}
        	else if((execution->threads == 256) && (currentThreads != 256)){
        		// Change directory to 256 threads compiled cudalign
        		printf("Changing directory to "CUDA256_DIR"\n");
        		sprintf(cudalignDir, CUDA256_DIR);
        		//printf("cd "CUDA256_DIR);
        		//system("cd "CUDA256_DIR);
        		currentThreads = 256;
        	}
        	
        	//1M
        	if(execution->size == 1){
        		sprintf(seqA, SEQ_DIR"/1M/"SEQ_1_A);
        		sprintf(seqB, SEQ_DIR"/1M/"SEQ_1_B);
        	}
        	
        	
            sprintf(exeLine, "%s/cudalign --ram-size=5G %s %s --blocks=%d", cudalignDir, seqA, seqB, execution->blocks);
			system(exeLine);
			
			
            // execute
            printf("Execution Line %d: %s\n", i, exeLine);
            //fetchResult(execution);

            execution = execution->next;
            i++;
        }

    }
}

void fetchResult(t_execution* execution){
    int stats[2];
    // change into temporary work directory

    readStats("/home/laicoadm/Documentos/Pedro/MASA_CUDAlign_256_threads", stats);

    printf("-Time: %d\n-MCups: %d\n", stats[0], stats[1]);

    execution->time = stats[0];
    execution->mcups = stats[1];
}



void testExeList(){

    insertExeList(1, 256, 512, 1);
    insertExeList(1, 128, 256, 1);
    //insertExeList(3, 64, 512, 0);
    //insertExeList(23, 128, 128, 0);
    //insertExeList(23, 128, 256, 0);
    //insertExeList(23, 128, 128, 1);
    //insertExeList(23, 128, 256, 1);

    runExeList();

    printExeList();
}
