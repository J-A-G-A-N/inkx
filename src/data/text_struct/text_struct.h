#include <stdlib.h>
#include <stdint.h>
#include "../gap_buffer/gap_buffer.h"


typedef struct{
    int pos;
    int index;
    char string[50];
    GapBuffer *gb;
}Text;

typedef struct{
	uint32_t curx, cury;
	uint32_t *cx, *cy; 
	uint32_t prev_curx , prev_cury;
	uint32_t *prev_cx, *prev_cy; 
}Cursor;


Text* InitText(size_t initial_size);
void DestroyText(Text*td);
