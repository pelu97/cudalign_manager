#include <stdio.h>
#include <stdlib.h>

#define FILE_SOURCE "../Stats-23M_64Threads_480Blocks_BP-01_20_50-15_07_22/statistics"


int isNumber(const char c){
    if(
        (c == '0') ||
        (c == '1') ||
        (c == '2') ||
        (c == '3') ||
        (c == '4') ||
        (c == '5') ||
        (c == '6') ||
        (c == '7') ||
        (c == '8') ||
        (c == '9')
    ){
        return 1;
    }
    else{
        return 0;
    }
}

int parseString(const char* string){
    int i, j, number;
    char parsedNumber[100];

    j=0;
    for(i=0; string[i]!='\0'; i++){
        printf("%c", string[i]);

        if(isNumber(string[i])){
            parsedNumber[j] = string[i];
            j++;
        }
        else if(string[i] == '.'){
            parsedNumber[j] = '\0';
            break;
        }
    }

    printf("String with number found: %s\n", parsedNumber);

    number = atoi(parsedNumber);

    return number;
}


int main(){
    FILE* filep;
    char string[500];
    int i;

    filep = fopen(FILE_SOURCE, "r");


    i=0;
    while(fgets(string, 500, filep)){
        printf("%s", string);

        if(i == 13){
            printf("__TOTAL__ %s", string);
            printf("%d", parseString(string));
        }

        if(i == 15){
            printf("__MCUPS__ %s", string);
            printf("%d", parseString(string));
        }

        i++;
    }


    return 0;
}
