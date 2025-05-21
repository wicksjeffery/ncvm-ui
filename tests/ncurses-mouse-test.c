
#include <curses.h>
#include <stdio.h>

int main()
{
	initscr();
	cbreak();
	// nocbreak();
	noecho();
	curs_set(0);
	// refresh();

	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLUE, COLOR_RED);

	bkgd(COLOR_PAIR(1));
	// refresh();


	WINDOW* awin = newwin(5, 10, 5, 5);
	box(awin, 0 , 0);
	wbkgd(awin,COLOR_PAIR(2) | A_BOLD);
	// wrefresh(awin);



  // // Enables keypad mode. This makes (at least for me) mouse events getting
  // // reported as KEY_MOUSE, instead as of random letters.
	keypad(stdscr, TRUE);
	keypad(awin, TRUE);
  //
  // // Don't mask any mouse events
  // mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	mousemask(BUTTON3_PRESSED, NULL);
	// refresh();
  //
  // printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
  //

	char char_arr [100];
	// int num = 42;



  for (;;) {
    int c = wgetch(awin);
	// wrefresh(awin);
	// int c = wgetch(stdscr);
	// int c = getch();

	sprintf(char_arr, "%d", c);


	// getch();
  //
  //   // Exit the program on new line fed
  //   if (c == '\n')
  //     break;
  //
    char buffer[512];
    size_t max_size = sizeof(buffer);
    // if (c == ERR) {
    //   snprintf(buffer, max_size, "Nothing happened.");
    // }
  //   else if (c == KEY_MOUSE) {
	if (c == KEY_MOUSE) {
	// if (c == BUTTON1_PRESSED) {
      MEVENT event;
      if (getmouse(&event) == OK) {
        snprintf(buffer, max_size, "Mouse at row=%d, column=%d bstate=0x%08lx",
                 event.y, event.x, event.bstate);
      }
  //     else {
  //       snprintf(buffer, max_size, "Got bad mouse event.");
  //     }
    // }
  //   else {
  //     snprintf(buffer, max_size, "Pressed key %d (%s)", c, keyname(c));
  //   }

  	mvprintw(2, 0, char_arr);
	// refresh();

	// if (wenclose(awin, event.y, event.x) == true)
	// {
		mvaddstr(0, 0, buffer);
    // addstr(buffer);
		// refresh();
	// wrefresh(awin);
	// }
	// if (wenclose(awin, event.y, event.x) == false)
	// {
	// 	mvaddstr(0, 0, " no  ");
 //    // addstr(buffer);
	// 	refresh();
	// }

	}



  }
  //
  // printf("\033[?1003l\n"); // Disable mouse movement events, as l = low

  endwin();

  return 0;
}
