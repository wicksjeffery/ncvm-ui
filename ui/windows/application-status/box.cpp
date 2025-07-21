#include "box.hpp"


UI::Windows::ApplicationStatus::Box::Box(int height, int width, int begin_y, int begin_x)
    :
        Rectangle(height, width, begin_y, begin_x)
{
    wbkgd(m_window, COLOR_PAIR(11));

    scrollok(m_window, TRUE);
}
