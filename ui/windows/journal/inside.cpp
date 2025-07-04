#include "inside.hpp"


UI::Windows::Journal::Inside::Inside(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(3));
    scrollok(m_window, TRUE);
}
