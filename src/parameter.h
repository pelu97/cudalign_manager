#include <stdio.h>

#ifndef PARAMETER_TYPE
#define PARAMETER_TYPE
typedef struct Parameter {
    int size;
    int threads;
    int blocks;
    struct Parameter *next;
} t_parameter;
#endif


extern t_parameter *BestParameters;


void addParameter(int size, int threads, int blocks);

void loadParameters();

void overwriteLine(char* newLine, FILE *fp, int overwritePosition);

void saveParameters(int size, int threads, int blocks);

void printParamaterTable();
