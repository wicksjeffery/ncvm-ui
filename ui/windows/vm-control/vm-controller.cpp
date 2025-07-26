#include "vm-controller.hpp"

#include <iostream>
#include "ncurses.h"
#include <cstring>

UI::Windows::VMControl::VMContoller::VMContoller(int begin_x)
    :
        Rectangle(7, 17, 3, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(5));
    // wbkgd(m_window, COLOR_PAIR(11));

    wattron(m_window, COLOR_PAIR(3));
    box(m_window ,0, 0);
    wattroff(m_window, COLOR_PAIR(3));



    int max_x = getmaxx(m_window); // Get the maximum column of the window.
    // const char* vm_name_tmp = "Fedora";
    // int text_len = strlen(vm_name_tmp); // Get the length of the text.
    // int start_col = (max_x - text_len) / 2; // Calculate the starting column.

    // mvwprintw(m_window, 2, start_col, "%s", vm_name_tmp, COLOR_PAIR(3));

    wattron(m_window, COLOR_PAIR(2));

    mvwhline(m_window, 5, 1, ACS_BLOCK, max_x-2);

    wattroff(m_window, COLOR_PAIR(2));
    wattron(m_window, COLOR_PAIR(3));

    mvwaddch(m_window, 4, 0, ACS_LTEE);
    mvwhline(m_window, 4, 1, ACS_HLINE, max_x-2);
    mvwaddch(m_window, 4, max_x-1, ACS_RTEE);
    wattroff(m_window, COLOR_PAIR(3));
    // wattron(m_window, COLOR_PAIR(3) | A_BOLD);

    // mvwaddch(m_window, 5, 1, ACS_RARROW);
    // mvwprintw(m_window, 5, 2, "%s", " sb: unknown"); //TODO: make 8max chars on left and : 8max chars on right
    // wattroff(m_window, COLOR_PAIR(3) | A_BOLD);

}
