
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



char getGrade(double inputValue){

    switch((int ) inputValue / 10){
        case 10:
        case 9: return 'A';
        case 8: return 'B';
        case 7: return 'C';
        case 6: return 'D';
       default: return 'F';
    }

    return 'F';

}



/*******************Get Value/Range Func.*****************/




int getInt(char *informationString){

    int inputValue = 0;

    printf("%s : ", informationString);
    scanf("%d", &inputValue);

    return inputValue;
}


double getDouble(char *informationString){

    double inputValue = 0;

    printf("%s ", informationString);
    scanf("%lf", &inputValue);

    return inputValue;
}


int getIntRange(char *informationString, int frontLimit, int rearLimit){

    int inputValue = 0;
    int isLoop = 0;

    while(!isLoop) {

        printf("%s (%d ~ %d) : ", informationString, frontLimit, rearLimit);
        scanf("%d", &inputValue);

        if( inputValue >= frontLimit && inputValue <= rearLimit){

            isLoop = 1;
        }
    }

    return inputValue;
}


double getDoubleRange(char *informationString, double frontLimit, double rearLimit){

    double inputValue = 0.0;
    int isLoop = 0;

    while(!isLoop){

        printf("%s (%.2lf ~ %.2lf) : ", informationString, frontLimit, rearLimit);
        scanf("%lf", &inputValue);

        if(inputValue >= frontLimit && inputValue <= rearLimit)
            isLoop = 1;
    }

    return inputValue;
}


/********** Char/String ************/

char getChar(char *informationString){

    char inputValue = 0;

    printf("%s : ", informationString);
    scanf("%c", &inputValue);

    return inputValue;
}


char* getStringByAddress(char *informationString, char *inputAddr){

    printf("%s : ", informationString);
    scanf("%s", inputAddr);


    return inputAddr;
}


/*****************Set Value Func.******************/



void setIntByAddress (int *inputAddr, int rawValue){ *inputAddr = rawValue; }
void setDoubleByAddress (double *inputAddr, double rawValue){ *inputAddr = rawValue; }
void setCharByAddress(char *inputAddr, char rawValue){ *inputAddr = rawValue; }
void setStringByAddress (char *inputAddr, char *rawValue){ strcpy(inputAddr, rawValue); }



/*****************Swap Value Func.********************/



void swapIntByAddress(int *dest, int *source){

    int buf = 0;

    buf = *dest;
    *dest = *source;
    *source = buf;
}


void swapDoubleByAddress(double *dest, double *source){

    double buf = 0.0;

    buf = *dest;
    *dest = *source;
    *source = buf;
}


void swapCharByAddress(char *dest, char *source){

    char buf = 0;

    buf = *dest;
    *dest = * source;
    *source = buf;

}


void swapStringByAddress(char *dest, char *source, int stringLength){

    char *buf = NULL;
    buf = (char *) calloc(stringLength, sizeof(char));
    //printf("\nbuf size : %d\n", msize(buf));


    strcpy(buf, dest);
    strcpy(dest, source);
    strcpy(source, buf);

    free(buf);
}
