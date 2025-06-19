#include "options.hpp"


UI::Windows::Options::Options(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(19));

    // BEGIN: give the box a "shadow"
    wattron(m_window, COLOR_PAIR(4));
    mvwvline(m_window, 0, width-1, ' ', height-1);
    mvwhline(m_window, height-1, 1, ' ', width-1);
    wattroff(m_window, COLOR_PAIR(4));

    wattron(m_window, COLOR_PAIR(4));
    mvwaddch(m_window, height-1, 0, ' '| COLOR_PAIR(2));
    wattroff(m_window, COLOR_PAIR(4));

    // END: give the box a "shadow"

    hide_panel(m_panel);
}

