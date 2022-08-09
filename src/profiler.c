#include "profiler.h"
#include "execution.h"
#include "analyser.h"
#include "parameter.h"



void createProfileComplete(){
    insertExeList("seq A path", "seq B path", 1, 512, 256, 1, 1);
}

void createProfileSimple(){
    // 5M
    // 128 threads
    // 256 blocks
    insertExeList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        128, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeList(
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
    insertExeList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        256, //blocks
        1, //bp
        1 //isProfile
    );
    // 480 blocks
    insertExeList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        480, //blocks
        1, //bp
        1 //isProfile
    );
    // 512 blocks
    insertExeList(
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_A,
        SEQ_DIR SEQ_5_DIR "/" SEQ_5_B,
        5, //size
        256, //threads
        512, //blocks
        1, //bp
        1 //isProfile
    );


    /* Example
    insertExeList(
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
    createProfileSimple();

    runExeList();
    printExeList();

    analyse();
    printAnalysisList();

    saveParameters(5, 256, 512);
}
