#include "profiler.h"
#include "execution.h"
#include "analyser.h"
#include "parameter.h"



void createProfileComplete(){
    insertExeInList("seq A path", "seq B path", 1, 512, 256, 1, 1);
}

void createProfileSimple(){
    // 5M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    /* Example
    insertExeInList(
        "seq A path",
        "seq B path",
        1, //size
        512, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    */

}


void runProfileComplete(){
    createProfileComplete();
    runExeList();
    printExeList();
}

void runProfileSimple(){
    t_analysis* analysis;

    createProfileSimple();

    runExeList();
    printExeList();

    analyse();
    printAnalysisList();

    analysis = AnalysisList;

    // check the analysis for each size and stores the best parameters found for that size in the file

    while(analysis != NULL){
        saveParameters(analysis->size, analysis->bestExecution->threads, analysis->bestExecution->blocks);
        analysis = analysis->next;
    }

}
