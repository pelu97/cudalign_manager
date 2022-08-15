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

extern int SimpleProfile;
extern int CompleteProfile;


void addParameter(int size, int threads, int blocks);

void loadParameters();

void insertLine(char* newLine, FILE *fp, long int insertPosition);

void overwriteLine(char* newLine, FILE *fp, long int overwritePosition);

void saveParameters(int size, int threads, int blocks);

void freeParameterTable();

void printParamaterTable();
