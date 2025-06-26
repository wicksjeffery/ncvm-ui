#include "about.hpp"

#include <iostream>

UI::Windows::MenuItems::About::About(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));

    wprintw(m_window, " About");
    hide_panel(m_panel);
}

