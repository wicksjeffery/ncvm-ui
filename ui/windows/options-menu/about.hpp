#ifndef ABOUT_HPP
#define ABOUT_HPP

#include "rectangle.hpp"


namespace UI::Windows::MenuItems
{
    class About : public Rectangle
    {
    public:
        About(int height, int width, int begin_y, int begin_x);
    };
}



#endif
