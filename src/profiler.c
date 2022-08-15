#include "profiler.h"
#include "execution.h"
#include "analyser.h"
#include "parameter.h"



void createProfileComplete(){
    // 1M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );



    // 3M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_A,
        SEQ_DIR SEQ_3_DIR "/" SEQ_3_B,
        3, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );



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


    // 10M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_A,
        SEQ_DIR SEQ_10_DIR "/" SEQ_10_B,
        10, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 23M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_A,
        SEQ_DIR SEQ_23_DIR "/" SEQ_23_B,
        23, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 47M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_A,
        SEQ_DIR SEQ_47_DIR "/" SEQ_47_B,
        47, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );
}

void createProfileSimple(){
    // 1M
    // 128 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        128, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    // 256 threads
    // 256 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeInList(
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_A,
        SEQ_DIR SEQ_1_DIR "/" SEQ_1_B,
        1, //size
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
    CompleteProfile = 1;
    finishProfile();
}

void runProfileSimple(){
    createProfileSimple();
    SimpleProfile = 1;
    finishProfile();
}

void finishProfile(){
    t_analysis* analysis;

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

    freeExeList();
}
