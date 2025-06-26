#ifndef INFORMATION_HPP
#define INFORMATION_HPP


#include "rectangle.hpp"


namespace UI::Windows
{
    class Information : public Rectangle
    {
    public:
        Information(int height, int width, int begin_y, int begin_x);
    };
}



#endif
