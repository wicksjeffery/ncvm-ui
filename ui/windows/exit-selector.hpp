#ifndef EXIT_SELECTOR_HPP
#define EXIT_SELECTOR_HPP

#include "rectangle.hpp"


namespace UI::Windows
{
    class ExitSelector : public Rectangle
    {
    public:
        ExitSelector(int height, int width, int begin_y, int begin_x);
    };
}



#endif
