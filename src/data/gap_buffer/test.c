#include <stdio.h>
#include "gap_buffer.h"
#include <string.h>
GapBuffer* gb1 ; 
GapBuffer* gb2 ; 
GapBuffer* gb3 ; 
GapBuffer* gb4 ; 
int testnum = 1 ; 
int compareStrings(char*actual,GapBuffer *gb){
    int bl = 0, b = 0, i = 0, c = 0;
    int strlength = strlen(actual);
    while (bl<gb->buffer_size) {
        if (gb->buffer[b]!=GAP_CHARACTER){
           if (actual[i]==gb->buffer[b]){
                i++;
                c++;
                printf("actual[%d]=%c,gb[%d]=%c\n",i,actual[i-1],b,gb->buffer[b]);
           } 
        }
        b++;
        bl++;
    }
    if (c==strlength){
        return 0 ;
    }
    else{
        return 1 ; 
    }
        printf("\n");

}
void jprint(char*actual,GapBuffer *gb){
    int len1 = strlen(actual) ;
    int len2 = 0;
    printf("Expected : ");
    for (int i = 0;i<len1;i++){
        printf("%c",actual[i]);
    }
    printf("\n");

    printf("Resulted : ");
    for (int i = 0;i<gb->buffer_size;i++){
        if (gb->buffer[i]!=GAP_CHARACTER){
            printf("%c",gb->buffer[i]);
            len2++; 
        }
            
    }
    printf("\n");
    printf("%d,%d\n",len1,len2) ; 
    printf("\n");

}
void Print(char*actual,GapBuffer *gb){
    if (compareStrings(actual,gb)==0){
        printf("Test passed test no : %d\n",testnum);
    }
    else{
        printf("Test failed test no : %d\n",testnum);
    }
    testnum++;
}


int main(){
    gb1 = InitGapBuffer(2) ; 
    gb2 = InitGapBuffer(2) ; 
    gb3 = InitGapBuffer(2) ; 
    gb4 = InitGapBuffer(2) ; 

    char actual1[] = "iamjagan" ;
    char teststring11[] = "iam";
    char teststring12[] = "jagan";
    int pos11 = 0 ; 
    int pos12 = 3 ; 

    char actual2[] = "Hello World" ;
    char teststring21[] = "Hello ";
    char teststring22[] = "World";
    int pos21 = 0 ; 
    int pos22 = 6 ;
   
    char actual3[] = "GEEKSFORGEEKS" ;
    char teststring31[] = "GEEKSGEEKS";
    char teststring32[] = "FOR";
    int pos31 = 0 ; 
    int pos32 = 5 ; 

     char actual4[] = "Hello World" ;
    char teststring41[] = "World";
    char teststring42[] = "Hello ";
    int pos41 = 0 ; 
    int pos42 = 0 ;
    printf("Testing Gapbuffer\n\n"); 

    InsertText(gb1, teststring11, 0);
    InsertText(gb1, teststring12, 3);
    Print(actual1,gb1);
    jprint(actual1,gb1);
    InsertText(gb2, teststring21, pos21);
    InsertText(gb2, teststring22, pos22);
    Print(actual2,gb2);
    jprint(actual2,gb2);

    InsertText(gb3, teststring31, pos31);
    InsertText(gb3, teststring32, pos32);
    Print(actual3,gb3);
    jprint(actual3,gb3);

    InsertText(gb4, teststring41, pos41);
    InsertText(gb4, teststring42, pos42);
    Print(actual4,gb4);
    jprint(actual4,gb4);


    DestroyGapBuffer(gb1);
    DestroyGapBuffer(gb2);
    DestroyGapBuffer(gb3);
    DestroyGapBuffer(gb4);

     return 0;
}
