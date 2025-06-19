#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <curses.h>
#include "rectangle.hpp"


namespace UI::Windows
{


    class Background : public Rectangle
    {
    public:
        const char* hello() const override
        {
            return "Hello from Background.";
        }

        Background(int height, int width, int begin_y, int begin_x);
    };
}



#endif
