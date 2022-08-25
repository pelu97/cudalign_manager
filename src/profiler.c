#include <stdio.h>
#include <stdlib.h>
#include "profiler.h"
#include "execution.h"
// #include "analyser.h"
#include "parameter.h"


// analysis

t_analysis* AnalysisList = NULL;


t_analysis* createAnalysis(int size, int bp){
    t_analysis *newAnalysis, *temp;

    newAnalysis = malloc(sizeof(t_analysis));

    newAnalysis->size = size;
    newAnalysis->bp = bp;
    // newAnalysis->bestTime = -1;
    // newAnalysis->bestMCups = -1;
    // newAnalysis->bestBlocks = -1;
    // newAnalysis->bestThreads = -1;
    newAnalysis->exeNumber = 0;
    newAnalysis->executions = NULL;
    newAnalysis->bestExecution = NULL;
    newAnalysis->next = NULL;


    if(AnalysisList == NULL){
        AnalysisList = newAnalysis;
    }
    else{
        temp = AnalysisList;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newAnalysis;
    }

    return newAnalysis;

}

void addExecution(t_analysis *analysis, t_execution *execution){
    t_execution **newExecutions;


    newExecutions = realloc(analysis->executions, sizeof(t_execution*) * (analysis->exeNumber + 1));

    if(newExecutions != NULL){
        newExecutions[analysis->exeNumber] = execution;
        analysis->executions = newExecutions;
        analysis->exeNumber++;

    }
    else{
        printf("Fatal error when reallocating memory for executions inside analysis of size %d\n", analysis->size);
    }
}

void addAnalysis(t_execution *execution){
    t_analysis *analysis;
    int found = 0;

    analysis = AnalysisList;

    while(analysis != NULL){
        // use sequence size and block pruning bool to group executions - blocks and threads can vary in each group
        if((analysis->size == execution->size) && (analysis->bp == execution->bp)){
            addExecution(analysis, execution);
            found = 1;
            break;
        }
        analysis = analysis->next;
    }

    // not found, created a new analysis with this size
    if(found == 0){
        analysis = createAnalysis(execution->size, execution->bp);
        addExecution(analysis, execution);
    }
}

void analyse(){
    t_execution *execution;
    t_analysis *analysis;
    int i, bestTime, bestMCups;

    execution = ExeList;

    // add all analysis with all executions
    while(execution != NULL){

        addAnalysis(execution);

        execution = execution->next;
    }

    analysis = AnalysisList;

    while(analysis != NULL){
        bestTime = 2147483647;
        bestMCups = -100;
        // find best execution
        for(i=0; i<analysis->exeNumber; i++){
            // found best time and best mcups (mcups and time are related, if one is the best, the other should also be, or something is not right)
            if((analysis->executions[i]->time < bestTime) && (analysis->executions[i]->mcups > bestMCups)){
                bestTime = analysis->executions[i]->time;
                bestMCups = analysis->executions[i]->mcups;
                analysis->bestExecution = analysis->executions[i];
            }
        }

        analysis = analysis->next;
    }
}

void printAnalysisList(){
    t_analysis *analysis;
    int i = 1, j;

    analysis = AnalysisList;

    #ifdef DEBUG
    if(analysis == NULL){
        printf("[DEBUG - ANALYSER] No analysis found\n");
    }
    #endif

    while(analysis != NULL){
        printf("-Analysis %d\n", i);
        printf("--Size: %d\n", analysis->size);
        printf("--BP: %d\n", analysis->bp);

        if(analysis->bestExecution != NULL){
            printf("--Best time: %d\n", analysis->bestExecution->time);
            printf("--Best MCups: %d\n", analysis->bestExecution->mcups);
            printf("--Best threads: %d\n", analysis->bestExecution->threads);
            printf("--Best blocks: %d\n", analysis->bestExecution->blocks);
        }
        else{
            printf("--Best execution not found yet\n");
        }

        printf("--Execution number: %d\n", analysis->exeNumber);

        if(analysis->exeNumber > 0){
            printf("--Executions: \n");
            for(j=0; j<analysis->exeNumber; j++){
                printf("---Threads: %d\n", analysis->executions[j]->threads);
                printf("---Blocks: %d\n", analysis->executions[j]->blocks);
                printf("---Time: %d\n", analysis->executions[j]->time);
                printf("---MCups: %d\n", analysis->executions[j]->mcups);
                printf("-----------\n");
            }
        }
        else{
            printf("--No executions\n");
        }
        i++;
        analysis = analysis->next;
    }
}


void freeAnalysisList(){
    t_analysis *analysis, *temp;

    analysis = AnalysisList;

    while(analysis != NULL){
        temp = analysis;
        analysis = analysis->next;

        free(temp->executions);
        free(temp);
    }
}


void testAnalysis(){
    testExeList();
    analyse();

    printAnalysisList();

}


// profiling


void createProfileComplete(){
    // 1M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );



    // 3M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );



    // 5M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 10M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 23M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 47M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );
}

void createProfileSimple(){
    // 1M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    /* Example
    insertExeInList(
        "seq A path",
        "seq B path",
        1, //size
        512, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    */

}


void runProfileComplete(){
    createProfileComplete();
    CompleteProfile = 1;
    finishProfile();
}

void runProfileSimple(){
    createProfileSimple();
    SimpleProfile = 1;
    finishProfile();
}

void finishProfile(){
    t_analysis* analysis;

    runExeList();
    printExeList();

    analyse();
    printAnalysisList();

    analysis = AnalysisList;

    // check the analysis for each size and stores the best parameters found for that size in the file

    while(analysis != NULL){
        saveParameters(analysis->size, analysis->bestExecution->threads, analysis->bestExecution->blocks);
        analysis = analysis->next;
    }

    freeExeList();

    loadParameters();
}
