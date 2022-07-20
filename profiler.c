#include <stdio.h>
#include <stdlib.h>
// #include "./src/parser.h"
// #include "./src/data.h"
#include "./src/execution.h"
#include "./src/analyser.h"

#define FILE_SOURCE "../Stats-23M_64Threads_480Blocks_BP-01_20_50-15_07_22/statistics"

// typedef struct Test{
//     int test1;
//     int test2;
//     int test3;
// } t_test;

int main(){
    // t_test **test;
    // test = NULL;
    // readFile(FILE_SOURCE);
    printf("\ntest\n");

    // testList();

    // test = realloc(test, (sizeof(t_test*) * 1));
    // test[0] = malloc(sizeof(t_test));
    // test[0]->test1 = 1;
    // test[0]->test2 = 2;
    // test[0]->test3 = 3;

    // test = realloc(test, sizeof(t_test*) * 2);
    // test[1]->test1 = 1;
    //
    // test = realloc(test, sizeof(t_test*) * 3);
    // test[2]->test1 = 1;

    // printf("%d\n", sizeof(*test[0]));
    // printf("%d %d %d\n", test[0]->test1, test[0]->test2, test[0]->test3);

    // inputExeList();
    // runExeList();
    testAnalysis();

    return 0;
}
