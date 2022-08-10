#include <stdio.h>
#include <stdlib.h>
// #include "./src/parser.h"
// #include "./src/data.h"
#include "./src/execution.h"
#include "./src/analyser.h"
#include "./src/profiler.h"
#include "./src/parameter.h"

#define FILE_SOURCE "../Stats-23M_64Threads_480Blocks_BP-01_20_50-15_07_22/statistics"

// typedef struct Test{
//     int test1;
//     int test2;
//     int test3;
// } t_test;


void confirmAlignment(){
    char buffer;

    printExeList();
    printf("The alignments listed above will be executed. Proceed? (Y/N)\n");

    scanf(" %c", &buffer);
    if((buffer == 'Y') || (buffer == 'y')){
        printf("Running execution list\n");
        runExeList();
        // checkFiles();
        printExeList();
    }
}


void importAlignmentFile(){
    char buffer;
    char seqA[4097], seqB[4097];
    FILE *fp;

    printf("Setup all the alignments using the file 'alignment_setup.txt' in the project directory.\n");
    printf("On each line, input the two sequences to be used in an alignment, using the following format:\n");
    printf("PATH_TO_SEQUENCE_A PATH_TO_SEQUENCE_B\n");
    printf("If the file is ready, press any key to continue...\n");
    scanf("%c", &buffer);
    scanf("%c", &buffer);


    fp = fopen("./alignment_setup.txt", "r");

    if(fp != NULL){
        // file opened without error
        while(fscanf(fp, "%s %s\n", seqA, seqB) != EOF){
            // seqA, seqB, size, blocks, threads, bp, isProfile
            insertExeInList(seqA, seqB, -1, -1, -1, 1, 0);
        }

        printf("Alignments read from file successfully!\n");
        // printExeList();
        confirmAlignment();
    }
    else{
        printf("An error ocurred when trying to acess the 'alignment_setup.txt' file. Check if it is in the project's directory.\n");
    }


}

void menu(){
    int choice, quit = 0, exeFilePending;

    while(!quit){
        exeFilePending = checkExeFile();

        printf("1 - Alignments\n");
        printf("2 - Profiling\n");
        if(exeFilePending){
            printf("3 - Restore last execution list\n");
            printf("4 - Quit\n");
        }
        else{
            printf("3 - Quit\n");
        }

        scanf("%d", &choice);

        if(choice == 1){
            choice = -1;

            while((choice != 1) && (choice != 2) && (choice != 3)){
                printf("1 - Input directly\n");
                printf("2 - Read from file\n");
                printf("3 - Back\n");

                scanf("%d", &choice);

                if(choice == 1){
                    printf("GET INPUT FROM USER\n");
                }
                else if(choice == 2){
                    // printf("READ FROM FILE\n");
                    importAlignmentFile();
                }
                else if(choice == 3){
                    printf("Going back\n");
                }
                else{
                    printf("Invalid option\n");
                }
            }

        }
        else if(choice == 2){
            choice = -1;

            while((choice != 1) && (choice != 2) && (choice != 3)){
                printf("1 - Complete profiling\n");
                printf("2 - Simplified profiling\n");
                printf("3 - Back\n");

                scanf("%d", &choice);

                if(choice == 1){
                    runProfileComplete();
                }
                else if(choice == 2){
                    runProfileSimple();
                }
                else if(choice == 3){
                    printf("Going back\n");
                }
                else{
                    printf("Invalid option\n");
                }
            }
        }
        else if(choice == 3){
            if(exeFilePending){
                loadExeFile();
                confirmAlignment();
            }
            else{
                printf("Quitting\n");
                quit = 1;
            }
        }
        else if(choice == 4){
            if(exeFilePending){
                printf("Quitting\n");
                quit = 1;
            }
            else{
                printf("Invalid option\n");
            }
        }
        else{
            printf("Invalid option\n");
        }
    }

}


int main(){
    // t_test **test;
    // test = NULL;
    // readFile(FILE_SOURCE);
    // printf("\ntest\n");

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
    // testAnalysis();


    loadParameters();
    // printParamaterTable();
    menu();

    return 0;
}
