#include <stdlib.h>
#include <stdio.h>
#include "execution.h"
#include "parser.h"

t_exelist* ExeList = NULL;

void insertExeList(int size, int threads, int blocks, int bp){
    t_exelist *newElement, *temp;

    newElement = malloc(sizeof(t_exelist));

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
    printf("Inserted value %d into list\n", value);
    #endif

}

void printExeList(){
    t_exelist *temp;
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
    t_exelist* temp;
    int i;
    char exeLine[300];

    temp = ExeList;

    if(temp == NULL){
        printf("No executions in list.\n");
    }
    else{
        i=1;
        while(temp != NULL){
            sprintf(exeLine, "./cudalign --ram-size=5G seq1 seq2 --blocks=%d", temp->blocks);

            // execute
            printf("Execution Line %d: %s\n", i, exeLine);
            fetchResult(temp);

            temp = temp->next;
            i++;
        }

    }
}

void fetchResult(t_exelist* execution){
    int stats[2];
    // change into temporary work directory

    readStats(stats);

    printf("-Time: %d\n-MCups: %d\n", stats[0], stats[1]);

    execution->time = stats[0];
    execution->mcups = stats[1];
}



void testExeList(){

    insertExeList(1, 64, 128, 1);
    insertExeList(1, 64, 256, 1);
    insertExeList(1, 64, 512, 0);
    insertExeList(1, 128, 128, 0);
    insertExeList(1, 128, 256, 0);

    printExeList();
}
