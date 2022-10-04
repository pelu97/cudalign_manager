#include "base.h"
#include "stdio.h"


#ifndef EXECUTION_TYPE
#define EXECUTION_TYPE
typedef struct Execution {
    char seqA[4097];
    char seqB[4097];
    char seqA_ID[50];
    char seqB_ID[50];
    int size;
    int threads;
    int blocks;
    int bp;
    int isProfile;
    int status; // 0 = waiting, 1 = completed
    // performance results
    int time;
    int mcups;
    struct Execution* next;
} t_execution;
#endif

extern t_execution* ExeList;
extern int CurrentThreads;
extern int ExeListLength;
extern int ExeListStatus; //0 = executing, 1 = completed

t_execution* insertExeInList(char* seqA, char* seqB, int size, int threads, int blocks, int bp, int isProfile);

void loadExeInList(char* seqA, char* seqB, int size, int threads, int blocks, int bp, int isProfile, int status, int time, int mcups);

void setExeSize(t_execution* execution, int size);

void printExeList();

void inputExeList();

void runExeList();

void fetchResult(t_execution* execution);

void getBestParam(int* paramsReturn, int size);

int getFileSize(FILE* fp);

int checkFiles();

void updateExeFile();

void loadExeFile();

int checkExeFile();

void freeExeList();

void testExeList();
