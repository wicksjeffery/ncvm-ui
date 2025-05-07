#include <ncurses.h>

int main() {
//     WINDOW *w;
    char c;

//     w = initscr();
    initscr();
    timeout(500);
    c = getch();
    endwin();

    printf("received %c (%d)\n", c, (int) c);
}
