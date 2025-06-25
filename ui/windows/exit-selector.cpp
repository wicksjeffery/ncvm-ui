#include "exit-selector.hpp"

#include <iostream>

UI::Windows::ExitSelector::ExitSelector(int height, int width, int begin_y, int begin_x)
:
Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));



    // // BEGIN: give the box a "shadow"
    // wattron(m_window, COLOR_PAIR(4));
    // mvwvline(m_window, 0, width-1, ' ', height-1);
    // mvwhline(m_window, height-1, 1, ' ', width-1);
    // // wattroff(m_window, COLOR_PAIR(4));
    //
    // // wattron(m_window, COLOR_PAIR(4));
    // mvwaddch(m_window, height-1, 0, ' '| COLOR_PAIR(1));
    // wattroff(m_window, COLOR_PAIR(4));
    // // END: give the box a "shadow"

    // mvwaddch(m_window, 0, 0, ACS_ULCORNER); // Top-left corner
    // mvwhline(m_window, 0, 1, 0, width-3);  // Top
    // mvwaddch(m_window, 0, width-2, ACS_URCORNER); // Top-right corner
    // mvwvline(m_window, 1, width-2, 0, height-3);  // Right border
    // mvwaddch(m_window, height-2, width-2, ACS_LRCORNER); // Bottom-right corner
    // mvwhline(m_window, height-2, 1, 0, width-3);  // Bottom
    // mvwaddch(m_window, height-2, 0, ACS_LLCORNER); // Bottom-left corner
    // mvwvline(m_window, 1, 0, 0, height-3);  // Left

    wprintw(m_window, " Exit");
    hide_panel(m_panel);
}

// // Invert colors - wattron(m_window, A_REVERSE) didn't work.
// void UI::Windows::OptionsSelector::toggleHighlighting()
// {
//     chtype background_attrs = getbkgd(m_window);
//     uint8_t color_pair_id = PAIR_NUMBER(background_attrs);
//
//     wbkgd(m_window, COLOR_PAIR(color_pair_id ^= 0x6));
// }
//
// void UI::Windows::OptionsSelector::turnOnHighlighting()
// {
//     wbkgd(m_window, COLOR_PAIR(5));
// }
//
// void UI::Windows::OptionsSelector::turnOffHighlighting()
// {
//     wbkgd(m_window, COLOR_PAIR(3));
// }
