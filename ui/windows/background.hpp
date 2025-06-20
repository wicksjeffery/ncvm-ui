#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <curses.h>
#include "rectangle.hpp"


namespace UI::Windows
{


    class Background : public Rectangle
    {
    public:

        Background(int height, int width, int begin_y, int begin_x);
    };
}



#endif
