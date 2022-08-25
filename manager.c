#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
// #include "./src/parser.h"
// #include "./src/data.h"
#include "./src/execution.h"
// #include "./src/analyser.h"
#include "./src/profiler.h"
#include "./src/parameter.h"

#define FILE_SOURCE "../Stats-23M_64Threads_480Blocks_BP-01_20_50-15_07_22/statistics"

// typedef struct Test{
//     int test1;
//     int test2;
//     int test3;
// } t_test;

void sighandler(int signum){
    printf("\nCaught signal %d - exitting\n", signum);
    exit(1);
}


void confirmAlignment(){
    char buffer;

    printExeList();
    printf("\nThe alignments listed above will be executed. Proceed? (Y/N)\n");

    scanf(" %c", &buffer);
    while((buffer != 'Y') && (buffer != 'y') && (buffer != 'N') && (buffer != 'n')){
        printf("Invalid option. Valid choices: (Y/y) for yes or (N/n) for no\n");
        scanf(" %c", &buffer);
    }
    if((buffer == 'Y') || (buffer == 'y')){
        printf("Running execution list\n");
        runExeList();
        // checkFiles();
        printExeList();

        freeExeList();
    }
    else if((buffer == 'N') || (buffer == 'n')){
        freeExeList();
    }
}


void importAlignmentFile(){
    char buffer;
    char seqA[4097], seqB[4097];
    FILE *fp;

    printf("\nSetup all the alignments using the file 'alignment_setup.txt' in the project directory.\n");
    printf("On each line of the file, input the two sequences to be aligned, using the following format:\n\n");
    printf("PATH_TO_SEQUENCE_A PATH_TO_SEQUENCE_B\n\n");
    printf("Example:\n\n");
    printf(".../seq/BA000035.2.fasta .../seq/BX927147.1.fasta\n\n");
    printf("The sequences must be in the fasta format.\n");
    printf("After running, the results of each alignment will be available in a folder inside the ./results/ directory.\n");
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

        fclose(fp);
        printf("Alignments read from file successfully!\n");
        // printExeList();
        confirmAlignment();
    }
    else{
        printf("An error ocurred when trying to access the 'alignment_setup.txt' file. Check if it is in the project's directory.\n");
    }


}


void quit(){
    printf("Quitting\n");

    freeParameterTable();
    freeAnalysisList();
    // freeExeList();
}


void menuProfile(){
    int choice = -1;

    while((choice != 1) && (choice != 2) && (choice != 3)){
        printf("───── Profiling Information ─────\n\n");
        printf("    A profile is useful to obtain the ideal parameters for your GPU, to ensure that the alignments will be executed as efficient and as fast as possible in your machine.\n");
        // printf("to ensure that the alignments will be executed as efficient and as fast as possible in your machine.\n");
        printf("    A complete profile will run several executions with different sizes of sequences. It will give the best results, but it will take hours to run. It only has to be executed once, unless the gpu in the machine is changed.\n");
        // printf("It will give the best results, but it will take hours to run. It only has to be executed once,\n");
        // printf("unless the gpu in the machine is changed.\n");
        printf("    A simple profile will run just a few executions and with small sequences. The results won't be as good as a complete profile, but it should take only a few minutes to run.\n");
        // printf("as a complete profile, but it should take only a few minutes to run.\n");
        printf("--- It is recommended to run at least the simplified profiling once. ---\n\n");

        printf("┌─────────────────────────┐\n");
        printf("│     Profiling Status    │\n");
        printf("│                         │\n");
        if(CompleteProfile){
            printf("│   Complete ["COLOR_GREEN"■"COLOR_RESET" - DONE]   │\n");
        }
        else{
            printf("│ Complete ["COLOR_RED"■"COLOR_RESET" - NOT DONE] │\n");
        }

        if(SimpleProfile){
            printf("│    Simple ["COLOR_GREEN"■"COLOR_RESET" - DONE]    │\n");
        }
        else{
            printf("│  Simple ["COLOR_RED"■"COLOR_RESET" - NOT DONE]  │\n");
        }

        printf("└─────────────────────────┘\n\n");

        // if(CompleteProfile){
        //     printf("1 - Complete profiling (DONE)\n");
        // }
        // else{
        //     printf("1 - Complete profiling (NOT DONE)\n");
        // }
        //
        // if(SimpleProfile){
        //     printf("2 - Simplified profiling (DONE)\n");
        // }
        // else{
        //     printf("2 - Simplified profiling (NOT DONE)\n");
        // }

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

void header(){
    printf("┌─────────────────────┐\n");
    printf("│  CUDAlign Profiler  │\n");
    printf("└─────────────────────┘\n");
    printf("\n\n");
}


void menu(){
    int choice, quitFlag = 0, exeFilePending;

    while(!quitFlag){
        exeFilePending = checkExeFile();

        clearTerminal();

        header();

        if(exeFilePending){
            printf("-- An unfinished execution list has been found. Choose option 4 to restore it --\n\n");
        }

        printf("1 - Alignments\n");
        printf("2 - Profiling\n");
        if(VerboseMode){
            printf("3 - Disable Verbose Mode (More information during the executions) (ENABLED)\n");
        }
        else{
            printf("3 - Enable Verbose Mode (More information during the executions) (DISABLED)\n");
        }
        if(exeFilePending){
            printf("4 - Restore unfinished execution list\n");
            printf("5 - Quit\n");
        }
        else{
            printf("4 - Quit\n");
        }

        scanf("%d", &choice);

        clearTerminal();

        if(choice == 1){
            choice = -1;

            while((choice != 1) && (choice != 2) && (choice != 3)){
                // printf("1 - Input directly\n");
                printf("1 - Read from file\n");
                printf("2 - Back\n");

                scanf("%d", &choice);

                // if(choice == 1){
                //     printf("GET INPUT FROM USER\n");
                // }
                if(choice == 1){
                    // printf("READ FROM FILE\n");
                    importAlignmentFile();
                }
                else if(choice == 2){
                    printf("Going back\n");
                }
                else{
                    printf("Invalid option\n");
                }
            }

        }
        else if(choice == 2){
            menuProfile();
            // choice = -1;

            // while((choice != 1) && (choice != 2) && (choice != 3)){
            //     printf("1 - Complete profiling\n");
            //     printf("2 - Simplified profiling\n");
            //     printf("3 - Back\n");
            //
            //     scanf("%d", &choice);
            //
            //     if(choice == 1){
            //         runProfileComplete();
            //     }
            //     else if(choice == 2){
            //         runProfileSimple();
            //     }
            //     else if(choice == 3){
            //         printf("Going back\n");
            //     }
            //     else{
            //         printf("Invalid option\n");
            //     }
            // }
        }
        else if(choice == 3){
            toggleVerboseMode();
        }
        else if(choice == 4){
            if(exeFilePending){
                loadExeFile();
                confirmAlignment();
            }
            else{
                quitFlag = 1;
                quit();
            }
        }
        else if(choice == 5){
            if(exeFilePending){
                quitFlag = 1;
                quit();
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

    signal(SIGINT, sighandler);

    // simulate gpu name
    // strcpy(CurrentGpu, "NVIDIA RTX 2060");

    // get gpu model
    getCurrentGpu();



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
