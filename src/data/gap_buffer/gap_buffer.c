#include "gap_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FERROR

GapBuffer *InitGapBuffer(size_t init_size ) {
    if (init_size==0){
        init_size = 1; 
    }
  GapBuffer *gap_buffer = (GapBuffer *)malloc(sizeof(GapBuffer));
  if (!gap_buffer) {
    fprintf(stderr, "Failed to allocate memory for gap_buffer");
#ifdef FERROR
	perrorfile("Failed to allocate memory for gap_buffer");
#endif /* ifdef FERROR */
    exit(1);
  }
  gap_buffer->buffer = (char *)malloc(sizeof(char) * init_size);
  if (!gap_buffer->buffer) {
    fprintf(stderr, "Failed to allocate memory for buffer");
#ifdef FERROR
	perrorfile("Failed to allocate memory for buffer");
#endif /* ifdef FERROR */
    exit(1);
  }
  gap_buffer->gap_start = 0;
  gap_buffer->cursor_pos = 0;
  gap_buffer->gap_size = init_size-1;
  gap_buffer->gap_end = init_size-1;
  gap_buffer->buffer_size = init_size;
  memset(gap_buffer->buffer,GAP_CHARACTER,gap_buffer->gap_size);
  return gap_buffer ; 
}
void DestroyGapBuffer(GapBuffer *gap_buffer) {
  free(gap_buffer->buffer);
  free(gap_buffer);
}

int GapBufferGrow(GapBuffer *gap_buffer, size_t inc_size) {

  char *temp = (char *)malloc(sizeof(char) * gap_buffer->buffer_size );
  // copy contents of gap_buffer to temp array
  memcpy(temp, gap_buffer->buffer + gap_buffer->cursor_pos,
         gap_buffer->buffer_size - gap_buffer->cursor_pos);
  // increase buffer size
  gap_buffer->buffer_size += inc_size;

  // reallocate memory for gap_buffer
  gap_buffer->buffer =
      realloc(gap_buffer->buffer, sizeof(char) * gap_buffer->buffer_size);
  if (!gap_buffer->buffer) {
    fprintf(stderr,"failed to reallocate memory for gap_buffer");
#ifdef FERROR
	perrorfile("failed to reallocate memory for gap_buffer");
#endif /* ifdef FERROR */
    free(temp);
    exit(1);
  }

  memcpy(gap_buffer->buffer + gap_buffer->cursor_pos + inc_size,
         gap_buffer->buffer + gap_buffer->cursor_pos,
         gap_buffer->buffer_size - gap_buffer->cursor_pos - inc_size);

  // Fill gap with GAP_CHARACTER
  memset(gap_buffer->buffer + gap_buffer->cursor_pos, GAP_CHARACTER, inc_size);
    gap_buffer->gap_size += inc_size ; 
  // Copy back content from temp to buffer
  memcpy(gap_buffer->buffer + gap_buffer->cursor_pos + inc_size, temp,
         gap_buffer->buffer_size - gap_buffer->cursor_pos - inc_size);

  // Update end position
  gap_buffer->gap_end += inc_size;

  // Destroy temp array
  free(temp);

  return 0;
}

int MoveFarward(GapBuffer *gap_buffer) {
  while (gap_buffer->cursor_pos < gap_buffer->gap_start) {
    gap_buffer->gap_start--;
    gap_buffer->gap_end--;
    gap_buffer->buffer[gap_buffer->gap_end+1] =
        gap_buffer->buffer[gap_buffer->gap_start];
    gap_buffer->buffer[gap_buffer->gap_start] = GAP_CHARACTER;
  }
  return 0;
}

int MoveBackward(GapBuffer *gap_buffer) {
  while (gap_buffer->cursor_pos > gap_buffer->gap_start) {
    gap_buffer->gap_start++;
    gap_buffer->gap_end++;
    gap_buffer->buffer[gap_buffer->gap_start-1] =
        gap_buffer->buffer[gap_buffer->gap_end];
    gap_buffer->buffer[gap_buffer->gap_end] = GAP_CHARACTER;
  }
  return 0;
}

int MoveCursor(GapBuffer *gap_buffer) {
  if (gap_buffer->cursor_pos < gap_buffer->gap_start) {
    MoveFarward(gap_buffer);
  } else {
    MoveBackward(gap_buffer);
  }
  return 0;
}

int InsertStringGB(GapBuffer *gap_buffer, const char *string, int position) {
  int stringlen = strlen(string);
  int i = 0;
  gap_buffer->cursor_pos = position;

  if (gap_buffer->cursor_pos != gap_buffer->gap_start) {
    MoveCursor(gap_buffer);
  }
  while (i < stringlen) {
    if (gap_buffer->gap_start == gap_buffer->gap_end) {
      GapBufferGrow(gap_buffer, stringlen);
    }

    gap_buffer->buffer[gap_buffer->gap_start] = string[i];
    gap_buffer->gap_start++;
    i++;
    gap_buffer->cursor_pos++;
  }
  return 0;
}

int DeleteStringGB(GapBuffer* gap_buffer,int position, size_t count) {
  gap_buffer->cursor_pos = position;
  if (gap_buffer->cursor_pos + 1 < gap_buffer->gap_start){
      MoveCursor(gap_buffer);
  }
  if (gap_buffer->cursor_pos < (int)gap_buffer->buffer_size){
      for (int i = 0; i < (int)count; i++ ){
          if (gap_buffer->gap_start > 0){
            gap_buffer->gap_start --;
            gap_buffer->buffer[gap_buffer->gap_start] = GAP_CHARACTER ; 
            gap_buffer->gap_size++;
          }
      }
  }
  return 0;
}
