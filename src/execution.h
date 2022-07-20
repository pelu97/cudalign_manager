// #define DEBUG

typedef struct ExecutionList {
    int size;
    int threads;
    int blocks;
    int bp;
    // performance results
    int time;
    int mcups;
    struct ExecutionList* next;
} t_exelist;

extern t_exelist* ExeList;


void insertExeList(int size, int threads, int blocks, int bp);

void printExeList();

void inputExeList();

void runExeList();

void fetchResult(t_exelist* execution);

void testExeList();
