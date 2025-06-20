#include "rectangle.hpp"
#include <curses.h>

UI::Windows::Rectangle::Rectangle()
{}

UI::Windows::Rectangle::Rectangle(int nlines, int ncols, int begin_y, int begin_x)
{
    m_window = newwin(nlines, ncols, begin_y, begin_x);

    m_panel = new_panel(m_window);
}

UI::Windows::Rectangle::~Rectangle()
{}
