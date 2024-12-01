#include <ncurses.h>
#include <string.h>
#include "data/dynamic_array/dynamicarray.h"
#include "io/io.h"
#include <stdint.h>
#include <sys/types.h>


#define DEBUG


Text* T ;
int ch = 0 ; 
int running = 1 ;
typedef struct{
	uint32_t curx, cury;
	uint32_t *cx, *cy; 
	uint32_t prev_curx , prev_cury;
	uint32_t *prev_cx, *prev_cy; 

}Cursor;

int main(int argc ,char*argv[]) {

	Cursor cursor; 
	cursor.cury = 0;
	cursor.curx = 0;
	cursor.cy = &cursor.cury;
	cursor.cx = &cursor.curx;

	// Initializing the Dynamic Array
	Dynamic_array* DA = CreateDA(1);

	// Set up the file name
	char flname[100];
    if (argc > 1){
        strcpy(flname,argv[1]);
     }
	
	#ifdef DEBUG
		// Clear the file 
		clearfile();

	#endif /* ifdef DEBUG */
	
    // Loading frame content
    LoadFile(flname,&T, cursor.cy,cursor.cx);
	
    // Initializing the screen 
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    refresh();


	// State Loop.
    while(running) {
       RenderTextT(T);
       ch = getch();
       if (ListenKeys(ch, cursor.cy, cursor.cx, &T, DA,argv[1])==false){
            running = 0;
       }
       refresh();
    }

	// Close the stdscr and deallocate heap memory.
    endwin();
    DestroyText(T);
	DestroyDA(DA);


	return 0;
}

