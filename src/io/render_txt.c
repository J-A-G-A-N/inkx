#include "render_txt.h"
#include <ncurses.h>


void RenderTextT(Text *T) {
    clear(); // Clear the screen
    int x = 0 , y = 0 ;

    for (int i = 0 ; i < T->gb->buffer_size ; i++){
        if (T->gb->buffer[i] != GAP_CHARACTER){
            addch(T->gb->buffer[i]);
            x++;
        }
        if (T->gb->buffer[i] == '\n'){
            y++;
            x = 0;
        }
    }
}

