#include <ncurses.h>
#include <string.h>
#include "data/dynamic_array/dynamicarray.h"
#include "io/io.h"
#include <stdint.h>
#include <sys/types.h>

#define DEBUG

Text* T ;
int running = 1 ;

int main(int argc ,char*argv[]) {

	int ch = 0 ; 
	Cursor cursor ; 
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
    LoadFile(flname,&T,&cursor);
	
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
       if (ListenKeys(ch, &cursor, &T, DA,argv[1])==false){
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

