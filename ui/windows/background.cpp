#include "background.hpp"

#include <iostream>

UI::Windows::Background::Background(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(2));

    wattron(m_window, COLOR_PAIR(3));
    mvwhline(m_window, 0, 0, ' ', width);
    wattroff(m_window, COLOR_PAIR(3));
}

