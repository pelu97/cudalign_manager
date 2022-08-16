#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cleanup.h"
#include "execution.h"
#include "base.h"



void cleanUp(t_execution* execution){
    // Move the alignment and statistics file to a folder acessible to the user
    // Use subfolders with names containing date, time, maybe even sequence names, to avoid overwriting any files
    // Clean the temporary work directory to prevent issues with the next alignment
    time_t rawtime;
    struct tm *timeinfo;
    char dirName[200], command[300];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(dirName, "%d_%02d_%02d-%02d_%02d_%02d-%s_%s",
        timeinfo->tm_year+1900,
        timeinfo->tm_mon+1,
        timeinfo->tm_mday,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec,
        execution->seqA_ID,
        execution->seqB_ID
    );


    sprintf(command, "mkdir -p "RESULT_DIR"/%s", dirName);

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Creating directory (%s)\n", command);
    #endif

    system(command);



    sprintf(command, "cp -v "WORK_DIR"/statistics "RESULT_DIR"/%s/statistics", dirName);

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Copying statistics file (%s)\n", command);
    #endif

    system(command);


    sprintf(command, "cp -v "WORK_DIR"/"ALIGN_FILE" "RESULT_DIR"/%s/"ALIGN_FILE, dirName);

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Copying alignment file (%s)\n", command);
    #endif

    system(command);


    cleanWorkDir();
    // sprintf(command, "rm -r "WORK_DIR);
    //
    // #ifdef DEBUG
    // printf("[DEBUG - CLEANUP] - Removing temporary work directory (%s)\n", command);
    // #endif
    //
    // // system(command);


    // printf("%s\n", dirName);

    // printf("Date time: %d/%d/%d - %d:%d:%d\n", timeinfo->tm_mday, timeinfo->tm_mon, timeinfo->tm_year, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);


}


void cleanWorkDir(){
    char command[210];
    sprintf(command, "rm -r "WORK_DIR);

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Removing temporary work directory (%s)\n", command);
    #endif

    system(command);
}

// maybe a final clean up, to clear the execution list file after all executions have been finished? Or add a way to check if the list was finished
//   before asking the user if he wants to restore the list.
