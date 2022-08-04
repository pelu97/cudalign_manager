#include "base.h"

// #define DEBUG

#ifndef EXECUTION_TYPE
#define EXECUTION_TYPE
typedef struct Execution {
    int size;
    int threads;
    int blocks;
    int bp;
    // performance results
    int time;
    int mcups;
    struct Execution* next;
} t_execution;
#endif

extern t_execution* ExeList;
extern int currentThreads;

void insertExeList(int size, int threads, int blocks, int bp);

void printExeList();

void inputExeList();

void runExeList();

void fetchResult(t_execution* execution);

void testExeList();
