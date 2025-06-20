#include "options-selector.hpp"


UI::Windows::OptionsSelector::OptionsSelector(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));
    wprintw(m_window, " Options ");
}

void UI::Windows::OptionsSelector::toggleSelected()
{
    chtype background_attrs = getbkgd(m_window);
    unsigned short color_pair_id = PAIR_NUMBER(background_attrs);

    wbkgd(m_window, COLOR_PAIR(color_pair_id ^= 0x6));
}
