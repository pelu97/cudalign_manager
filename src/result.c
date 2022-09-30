#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "execution.h"
#include "result.h"
#include "base.h"


#define FILE_SOURCE "../Stats-23M_64Threads_480Blocks_BP-01_20_50-15_07_22/statistics"




int isNumber(const char c){
    if(
        (c == '0') ||
        (c == '1') ||
        (c == '2') ||
        (c == '3') ||
        (c == '4') ||
        (c == '5') ||
        (c == '6') ||
        (c == '7') ||
        (c == '8') ||
        (c == '9')
    ){
        return 1;
    }
    else{
        return 0;
    }
}

int parseString(const char* string){
    int i, j, number;
    char parsedNumber[100];

    j=0;
    for(i=0; string[i]!='\0'; i++){
        // printf("%c", string[i]);

        if(isNumber(string[i])){
            parsedNumber[j] = string[i];
            j++;
        }
        else if(string[i] == '.'){
            parsedNumber[j] = '\0';
            break;
        }
    }

    // printf("String with number found: %s\n", parsedNumber);

    number = atoi(parsedNumber);

    return number;
}


void readFile(const char* fileSource){
    FILE* filep;
    char string[500];
    int i;

    filep = fopen(fileSource, "r");


    i=0;
    while(fgets(string, 500, filep)){
        printf("%s", string);

        if(i == 13){
            printf("__TOTAL__ %s", string);
            printf("%d", parseString(string));
        }

        if(i == 15){
            printf("__MCUPS__ %s", string);
            printf("%d", parseString(string));
        }

        i++;
    }

    fclose(filep);
}

void readStats(int* stats){
    FILE* filep;
    char string[500];
    int i;

	// sprintf(fileSource, "%s"WORK_DIR"/statistics", cudalignDir);

    //filep = fopen(FILE_SOURCE, "r");

    filep = fopen(WORK_DIR"/statistics", "r");

    // #ifdef DEBUG
    // printf("[DEBUG - PARSER] Stats file: %s\n", fileSource);
    // #endif

    #ifdef DEBUG
    printf("[DEBUG - PARSER] Reading statistics from file\n");
    #endif

    i=0;
    while(fgets(string, 500, filep)){
        // printf("%s", string);

        if(i == 13){
            // printf("__TOTAL__ %s", string);
            stats[0] = parseString(string);
        }

        if(i == 15){
            // printf("__MCUPS__ %s", string);
            stats[1] = parseString(string);
        }

        i++;
    }

    fclose(filep);

}


// clean up

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

    if(VerboseMode){
        sprintf(command, "mkdir -p "RESULT_DIR"/%s", dirName);
    }
    else{
        sprintf(command, "mkdir -p "RESULT_DIR"/%s > /dev/null", dirName);
    }

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Creating directory (%s)\n", command);
    #endif

    system(command);


    if(VerboseMode){
        sprintf(command, "cp -v "WORK_DIR"/statistics "RESULT_DIR"/%s/statistics", dirName);
    }
    else{
        sprintf(command, "cp -v "WORK_DIR"/statistics "RESULT_DIR"/%s/statistics > /dev/null", dirName);
    }

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Copying statistics file (%s)\n", command);
    #endif

    system(command);


    if(VerboseMode){
        sprintf(command, "cp -v "WORK_DIR"/"ALIGN_FILE" "RESULT_DIR"/%s/"ALIGN_FILE, dirName);
    }
    else{
        sprintf(command, "cp -v "WORK_DIR"/"ALIGN_FILE" "RESULT_DIR"/%s/"ALIGN_FILE"  > /dev/null", dirName);
    }

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

    if(VerboseMode){
        sprintf(command, "rm -r "WORK_DIR);
    }
    else{
        sprintf(command, "rm -r "WORK_DIR" > /dev/null 2>&1");
    }

    #ifdef DEBUG
    printf("[DEBUG - CLEANUP] - Removing temporary work directory (%s)\n", command);
    #endif

    // system(command);
}

// maybe a final clean up, to clear the execution list file after all executions have been finished? Or add a way to check if the list was finished
//   before asking the user if he wants to restore the list.
