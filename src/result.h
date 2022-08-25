#include "base.h"
#include "execution.h"

int isNumber(const char c);

int parseString(const char* string);

void readFile(const char* fileSource);

void readStats(int* stats);

// clean up

void cleanUp(t_execution* execution);

void cleanWorkDir();