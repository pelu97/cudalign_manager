// General definitions to be used by various/all files




// Best parameters file
#ifndef PARAM_FILE
#define PARAM_FILE "./parameters.txt"
#endif

// Default parameters
#ifndef DEFAULT_THREADS
#define DEFAULT_THREADS 256
#endif

#ifndef DEFAULT_BLOCKS
#define DEFAULT_BLOCKS 480
#endif

// Execution list file
#ifndef EXE_FILE
#define EXE_FILE "./execution.txt"
#endif

// Results directory
#ifndef RESULT_DIR
#define RESULT_DIR "./results"
#endif

// Work directory
#ifndef WORK_DIR
#define WORK_DIR "./work.tmp"
#endif

// Alignment file
#ifndef ALIGN_FILE
#define ALIGN_FILE "alignment.00.txt"
#endif

// CUDAlign directories
#ifndef CUDA64_DIR
#define CUDA64_DIR "/home/laicoadm/Documentos/Pedro/MASA_CUDAlign_64_threads"
#endif

#ifndef CUDA128_DIR
#define CUDA128_DIR "./cudalign/128_threads"
// #define CUDA128_DIR "/home/laicoadm/Documentos/Pedro/MASA_CUDAlign_128_threads"
#endif

#ifndef CUDA256_DIR
#define CUDA256_DIR "./cudalign/256_threads"
#endif


// Sequence directories
#ifndef SEQ_DIR
#define SEQ_DIR "./seq"
#endif

#ifndef SEQ_1_DIR
#define SEQ_1_DIR "/1M"
#endif

#ifndef SEQ_3_DIR
#define SEQ_3_DIR "/3M"
#endif

#ifndef SEQ_5_DIR
#define SEQ_5_DIR "/5M"
#endif

#ifndef SEQ_10_DIR
#define SEQ_10_DIR "/10M"
#endif

#ifndef SEQ_23_DIR
#define SEQ_23_DIR "/23M"
#endif

#ifndef SEQ_47_DIR
#define SEQ_47_DIR "/47M"
#endif


//Sequence File Names
// 1M
#ifndef SEQ_1_A
#define SEQ_1_A "AE002160.2.fasta"
#endif
#ifndef SEQ_1_B
#define SEQ_1_B "CP000051.1.fasta"
#endif

// 3M
#ifndef SEQ_3_A
#define SEQ_3_A "BA000035.2.fasta"
#endif
#ifndef SEQ_3_B
#define SEQ_3_B "BX927147.1.fasta"
#endif

// 5M
#ifndef SEQ_5_A
#define SEQ_5_A "AE016879.1.fasta"
#endif
#ifndef SEQ_5_B
#define SEQ_5_B "AE017225.1.fasta"
#endif

// 10M
#ifndef SEQ_10_A
#define SEQ_10_A "NC_014318.1.fasta"
#endif
#ifndef SEQ_10_B
#define SEQ_10_B "NC_017186.1.fasta"
#endif

// 23M
#ifndef SEQ_23_A
#define SEQ_23_A "NT_037436.4.fasta"
#endif
#ifndef SEQ_23_B
#define SEQ_23_B "NT_033779.5.fasta"
#endif

// 47M
#ifndef SEQ_47_A
#define SEQ_47_A "BA000046.3.fasta"
#endif
#ifndef SEQ_47_B
#define SEQ_47_B "NC_000021.9.fasta"
#endif


// Debug flag - enables debug prints inside modules
#ifndef DEBUG
#define DEBUG
#endif

// Dummy flag - useful for debugging, enable execution of dummy programs to simulate executions
// #ifndef DUMMY
// #define DUMMY
// #endif

// Flag to disable terminal clearing. Useful for debugging, should be disabled in the final build
#ifndef DISABLE_CLEAR
#define DISABLE_CLEAR
#endif


extern int VerboseMode;

extern char CurrentGpu[200];

void clearTerminal();

void toggleVerboseMode();

void getCurrentGpu();


// Colors
#ifndef COLORS
#define COLOR_RESET "\x1b[0m"
#define COLOR_BLACK "\x1b[30m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_WHITE "\x1b[37m"
#define COLORS
#endif
