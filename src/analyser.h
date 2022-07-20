#include "execution.h"
#include "base.h"


typedef struct Analysis {
    int size;
    int bp;
    // int bestTime;
    // int bestMCups;
    // int bestBlocks;
    // int bestThreads;
    int exeNumber;
    t_execution **executions;
    t_execution *bestExecution;
    struct Analysis *next;
} t_analysis;


extern t_analysis *AnalysisList;

t_analysis* createAnalysis(int size, int bp);

void addExecution(t_analysis *analysis, t_execution *execution);

void addAnalysis(t_execution *execution);

void analyse();

void printAnalysisList();

void testAnalysis();
