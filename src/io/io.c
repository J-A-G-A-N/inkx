#include "io.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

bool ifspace = 0 ; 
int count = 0;
char errorbuffer[100];
uint32_t newline_char_count = 0;

//
// void reset_curpos(GapBuffer* gb , uint32_t* curx){
// 	if (count == 0){
// 		gb->cursor_pos = 0;
// 		*curx = 0;
// 		count++;
//
// 	}
// }



bool ListenKeys(int character,Cursor *cursor_ptr, Text** T, Dynamic_array*DA, char *filename){
	cursor_ptr->prev_curx =  cursor_ptr->prev_cury = 0;
	cursor_ptr->prev_cx = &cursor_ptr->curx; 
	cursor_ptr->prev_cy = &cursor_ptr->cury;

    char c = (char) character;
    switch(character){

        case is_ctrl('e'):
            return false;

        case is_ctrl('w'):
            SaveFile(filename,T);
            break;

        case KEY_UP:
            if (cursor_ptr->curx >0){cursor_ptr->cury--;}
				//cursor_ptr->prev_cy = &cursor_ptr->cury;
            break;
            
        case KEY_DOWN:
			cursor_ptr->prev_cy = &cursor_ptr->cury;
            cursor_ptr->cury++;
            break;

        case KEY_LEFT:
           if (0 < cursor_ptr->curx && 0< ((*T)->gb->cursor_pos)){
				cursor_ptr->prev_cx = &cursor_ptr->curx;
                cursor_ptr->curx-- ; 
                (*T)->gb->cursor_pos--;
           }
		   break;

        case KEY_RIGHT:
				cursor_ptr->prev_cx = &cursor_ptr->curx;
				(*T)->gb->cursor_pos++;
				cursor_ptr->curx++;
				break;            

        case 10:
			cursor_ptr->prev_cy = &cursor_ptr->cury;
			cursor_ptr->cury++;
			cursor_ptr->prev_cx = &cursor_ptr->curx;
            cursor_ptr->curx = 0;
			InsertStringGB((*T)->gb, "\n",(*T)->gb->cursor_pos);
            break;

        case KEY_BACKSPACE:
			sprintf(errorbuffer,"\n cur y == %d\n",cursor_ptr->cury);
			perrorfile(errorbuffer);
			
			if (cursor_ptr->curx == 0 && cursor_ptr->cury != 0 ){
					cursor_ptr->cury--;
			}

			if ((cursor_ptr->curx != 0 ) && (*T)->gb->cursor_pos > 0){

                DeleteStringGB((*T)->gb,(*T)->gb->cursor_pos, 1);

                (*T)->gb->cursor_pos--;
                cursor_ptr->curx--;

				break;
            }

        case KEY_DC:
            break;

        case KEY_STAB:
        //     cursor_ptr->curx +=4 ;
        //     break;
        
        default:
            //(*T)->string[(*T)->index] = c ; 
			//reset_curpos((*T)->gb, curx);
            InsertStringGB((*T)->gb,&c,(*T)->gb->cursor_pos);
            cursor_ptr->curx++;
            break;
    }
	sprintf(errorbuffer,"\n(curx, cury) = (%d, %d) , cursor position : %d",cursor_ptr->curx, cursor_ptr->cury, (*T)->gb->cursor_pos); 
	perrorfile(errorbuffer);

    move(cursor_ptr->cury,cursor_ptr->curx);
    return true ; 
}


bool LoadFile(char * filename , Text** T, Cursor *cursor_ptr) {
  FILE *file;
  int filesize;

  file = fopen(filename, "rb");


  if (!file) {
	sprintf(errorbuffer,"Could not open file %s\n", filename);
	perrorfile(errorbuffer);
    return false;
  }

  // Seek to the end of the file
  fseek(file, 0, SEEK_END);

  filesize = ftell(file);

  fclose(file);

  *T = InitText(filesize);
  file = fopen(filename, "r");

  if (!file) {
	sprintf(errorbuffer,"Could not open file %s\n", filename);
	perrorfile(errorbuffer);
    return false;
  }

  int cursor_pos = (*T)->gb->gap_start;
  char *temp = malloc(sizeof(char) * filesize);
  while (fgets(temp, sizeof(temp), file)) {
    InsertStringGB((*T)->gb, temp, cursor_pos);
	uint32_t stringlength = strlen(temp);
	cursor_ptr->curx = stringlength ; 
    cursor_pos += stringlength;
  }
    free(temp); 
  return true;
}





bool SaveFile(char *filename,Text** T) {
  FILE *file = fopen(filename, "w");

  if (file == NULL)
    return 1;

  // Write the text before the gap
  for (int i = 0; i < (*T)->gb->gap_start; i++) {
    if ((*T)->gb->buffer[i] != GAP_CHARACTER) {
      fputc((*T)->gb->buffer[i], file);
    }
  }

  // Write the text after the gap
  for (int i = (*T)->gb->gap_end; i < (int)(*T)->gb->buffer_size; i++) {
    if ((*T)->gb->buffer[i] != GAP_CHARACTER) {
      fputc((*T)->gb->buffer[i], file);
    }
  }

  fclose(file);
  return 0; 
}
	
uint32_t index_of_newline(Dynamic_array* DA, int num){
	/*
		The index in the nth no of \n character while the respective number is the index pos
	 */
	return DA->aptr[num];
}

// bool jumppreviousline(Text *T, Dynamic_array* DA, uint32_t cury, uint32_t curx){
// 		 		
// 	return true ; 
// }
