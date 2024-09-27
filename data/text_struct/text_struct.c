#include "text_struct.h"
#include <stdio.h>
#include <stdlib.h>


Text* InitText(size_t initial_size) {
    Text* td = (Text*)malloc(sizeof(Text));
    if (td == NULL){
        fprintf(stderr,"Unable to allocate memory for Text data structure \n");
		perrorfile("Unable to allocate memory for Text data structure \n");
    }
    td->gb = InitGapBuffer(initial_size);
    if (td->gb == NULL){
        fprintf(stderr,"Unable to allocate memory for Text data structure \n");
		perrorfile("Unable to allocate memory for Text data structure \n");
    }    return td ;  
    td->pos = td->index = 0 ;
}
void DestroyText(Text*td){
    DestroyGapBuffer(td->gb);
    free(td);
}


