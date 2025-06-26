#include "options-button.hpp"

#include <iostream>

UI::Windows::OptionsButton::OptionsButton(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));
    wprintw(m_window, " Options ");
}

// Invert colors - wattron(m_window, A_REVERSE) didn't work.
void UI::Windows::OptionsButton::toggleHighlighting()
{
    chtype background_attrs = getbkgd(m_window);
    uint8_t color_pair_id = PAIR_NUMBER(background_attrs);

    wbkgd(m_window, COLOR_PAIR(color_pair_id ^= 0x6));
}

void UI::Windows::OptionsButton::turnOnHighlighting()
{
    wbkgd(m_window, COLOR_PAIR(5));
}

void UI::Windows::OptionsButton::turnOffHighlighting()
{
    wbkgd(m_window, COLOR_PAIR(3));
}
