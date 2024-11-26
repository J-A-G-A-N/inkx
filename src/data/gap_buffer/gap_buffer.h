#ifndef GAP_BUFFER_H_
#define GAP_BUFFER_H_
#include <stdlib.h>
#include "../../ferror.h"
#define GAP_CHARACTER '\0'

typedef struct {
    char *buffer;
    int gap_start ; 
    int gap_end;
    int cursor_pos;
    size_t buffer_size;
    size_t gap_size;
} GapBuffer;

GapBuffer* InitGapBuffer(size_t initial_size);
void DestroyGapBuffer(GapBuffer* gap_buffer);
int InsertStringGB(GapBuffer* gap_buffer, const char * string, int position ) ; 
int MoveCursor(GapBuffer* gap_buffer);
int MoveFarward(GapBuffer* gap_buffer);
int MoveBackward(GapBuffer* gap_buffer);
int GapBufferGrow(GapBuffer* gap_buffer,size_t inc_size) ; 
int DeleteStringGB(GapBuffer* gap_buffer,int position, size_t count) ;

#endif // !GAP_BUFFER_H_
