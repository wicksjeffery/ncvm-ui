#include <ncurses.h>

int main()
{	
	initscr();			/* Start curses mode 		  */
    move(0, 0);
    addch(ACS_DIAMOND);
    move(2, 2);
    addch(ACS_DEGREE);
    move(3, 3);
/*    
    int ch;
    ch = getch();
        if(ch == KEY_LEFT)
        printw("Left arrow is pressed\n");
*/	
    printw("height: %d, width: %d", COLS, LINES);	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}

