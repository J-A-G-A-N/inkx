#include "gap_buffer.h"
#include <stdio.h>

GapBuffer* gb ;  
int gap_count = 0 ; 

void Print(){
    for (int i = 0 ; i < gb->buffer_size ; i++){
       if (gb->buffer[i]!=GAP_CHARACTER){
            printf("%c",gb->buffer[i]);
        }
       else{
           gap_count++;
           printf("!");
       }
   }
    printf("\n");
}


int main(){
    char string1[10]; 
    int pos1 = 0 ; 
    int pos2 = 0 ;
    int delete_length = 0;
    gb = InitGapBuffer(2);
    if (!gb){
        printf("Initialization Failed\n");
    }
    else{
        printf("Initialization Success\n");
    }
    Print();
    printf("Enter a string to add : \n");
    scanf("%s",string1);
    printf("Enter the position : \n") ; 
    scanf("%d",&pos1);
    InsertText(gb,string1, pos1);
    printf("Enter a string to add : \n");
    scanf("%s",string1);
    printf("Enter the position : \n") ; 
    scanf("%d",&pos1);
    InsertText(gb,string1,pos1);
    Print();
    // printf("Enter the lenght of character to be deleted:\n");
    // scanf("%d",&delete_length);
    // printf("Enter the position : \n") ; 
    // scanf("%d",&pos1);
    // DeleteText(gb,pos1,delete_length);
    // Print();
    // printf("GapBuffer gap Size : %zu\n",gb->gap_size);
    // printf("gapcount:%d\n",gap_count);
    // printf("Gapbuffer");
     DestroyGapBuffer(gb); 

    return 0; 
}
