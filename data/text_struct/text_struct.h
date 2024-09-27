#include <stdlib.h>
#include "../gap_buffer/gap_buffer.h"


typedef struct{
    int pos;
    int index;
    char string[50];
    GapBuffer *gb;
}Text;

Text* InitText(size_t initial_size);
void DestroyText(Text*td);
