#include <ncurses.h>
#include <string.h>
#include "data/dynamic_array/dynamicarray.h"
#include "io/io.h"
#include <stdint.h>
#include <sys/types.h>

uint32_t curx = 0 , cury = 0 ;
Text* T ;
uint32_t *cx = &curx , *cy = &cury; 
int ch = 0 ; 
int running = 1 ;

int main(int argc ,char*argv[]) {
	Dynamic_array* DA = CreateDA(1);
	char flname[100];
    if (argc > 1){
        strcpy(flname,argv[1]);
     }
	clearfile();
    // Loading frame content
    LoadFile(flname,&T, cy,cx);
	//T->gb->cursor_pos = 0;
    // Initializing the screen 
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);

    refresh();

    while(running) {
       RenderTextT(T);
       ch = getch();
       if (ListenKeys(ch, cy, cx, &T, DA,argv[1])==false){
            running = 0;
       }
       refresh();
    }
    endwin();
    DestroyText(T);
	DestroyDA(DA);
     return 0;
}

