#ifndef EXIT_HPP
#define EXIT_HPP

#include "rectangle.hpp"


namespace UI::Windows::MenuItems
{
    class Exit : public Rectangle
    {
    public:
        Exit(int height, int width, int begin_y, int begin_x);
    };
}



#endif
