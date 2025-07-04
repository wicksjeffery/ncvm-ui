#include "outter-frame.hpp"


UI::Windows::Journal::OutterFrame::OutterFrame(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));

    // BEGIN: give the box a "shadow"
    wattron(m_window, COLOR_PAIR(4));
    mvwvline(m_window, 1, width-1, ' ', height-2);
    mvwhline(m_window, height-1, 1, ' ', width-1);
    wattroff(m_window, COLOR_PAIR(4));
    // END: give the box a "shadow"

    // BEGIN: Inside box
    wattron(m_window, COLOR_PAIR(2) | A_BOLD);
    mvwaddch(m_window, 0, 1, ACS_ULCORNER); // Top-Left corner
    mvwhline(m_window, 0, 2, ACS_HLINE, width-4); // Top horizontal
    mvwaddch(m_window, 0, width-3, ACS_URCORNER); // Top-right corner
    mvwvline(m_window, 1, width-3, ACS_VLINE, height-3); // Right vertical
    mvwaddch(m_window, height-2, width-3, ACS_LRCORNER); // Lower-right corner
    mvwhline(m_window, height-2, 2, ACS_HLINE, width-5);
    mvwaddch(m_window, height-2, 1, ACS_LLCORNER); // Lower-Left corner
    mvwvline(m_window, 1, 1, ACS_VLINE, height-3);
    wattroff(m_window, COLOR_PAIR(2) | A_BOLD);
    // END: Inside box

    // Hardcode top right and bottom left characters to
    // give a transparent look.
    mvwaddch(m_window, 0, width-1, ' ' | COLOR_PAIR(1));
    mvwaddch(m_window, height-1, 0, ' ' | COLOR_PAIR(1));
}
