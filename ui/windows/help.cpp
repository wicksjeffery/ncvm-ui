#include "help.hpp"
#include "curses.h"

UI::Windows::Help::Help(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));

    // BEGIN: give the box a "shadow"
    wattron(m_window, COLOR_PAIR(4));
    mvwvline(m_window, 1, width-1, ' ', height-2);
    mvwhline(m_window, height-1, 1, ' ', width-1);
    wattroff(m_window, COLOR_PAIR(4));

    // Hardcode top right and bottom left characters to
    // give a transparent look.
    mvwaddch(m_window, 0, width-1, ' ' | COLOR_PAIR(1));
    mvwaddch(m_window, height-1, 0, ' ' | COLOR_PAIR(1));

    // END: give the box a "shadow"

    /*
     * The following is to fix the shadow on the top right and
     * bottom left, where the character should be the same as
     * what's below it (so it appears transparent). This is for
     * window decoration/style. This is incomplete because
     * I need to translate: I.E. the top right corner X,Y needs
     * to be translated to that position, in the window/panel
     * underneath so the code can be truely dynamic (no
     * knowledge of the window/panel underneath is neccessary.)
     *
     * However, for now, I'll just hardcode the characters as
     * blue spaces because it might be uneccessary to do more.
    */

    // // PANEL *second_panel = panel_below(m_panel);
    // WINDOW* window_below = panel_window(panel_below(m_panel));
    //
    // // Get the chtype value at the top right position because this character should appear transparent.
    // // chtype right_top = mvwinch(window_below, 0, width-1);
    // chtype right_top = mvwinch(window_below, 3, COLS-3);
    //
    // // // Extract character
    // // char character = right_top & A_CHARTEXT;
    // //
    // // // Extract attributes
    // // int attributes = right_top & (~A_CHARTEXT);
    // //
    // // // Extract color pair
    // // int color_pair = PAIR_NUMBER(right_top);
    // //
    // // mvwprintw(m_window, 1, 1, "Character: %c\n", character);
    // // mvwprintw(m_window, 2, 1, "Attributes: %d\n", attributes);
    // // mvwprintw(m_window, 3, 1, "Color Pair: %d\n", color_pair);
    //
    // mvwaddch(m_window, 0, width-1, right_top & A_CHARTEXT | COLOR_PAIR(PAIR_NUMBER(right_top)) | right_top & (~A_CHARTEXT));
    //
    // // int max_y, max_x;
    // // getmaxyx(window_below, max_y, max_x);
    // // mvwprintw(m_window, 0, 0, "stdscr size: %d rows, %d columns\n", LINES, COLS);
    // // mvwprintw(m_window, 1, 0, "Window size: %d rows, %d columns\n", max_y, max_x);
    //
    // chtype bottom_left = mvwinch(window_below, LINES-3, 3);
    // mvwaddch(m_window, height-1, 0, bottom_left & A_CHARTEXT | COLOR_PAIR(PAIR_NUMBER(bottom_left)) | bottom_left & (~A_CHARTEXT));





}
