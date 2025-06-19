#include "options-selector.hpp"


UI::Windows::OptionsSelector::OptionsSelector(int height, int width, int begin_y, int begin_x)
:
Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(19));
    // wbkgd(m_window, COLOR_PAIR(14)); //TESTING

    wprintw(m_window, " Options ");
}
