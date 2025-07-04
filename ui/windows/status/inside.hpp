#ifndef STATUS_INSIDE_HPP
#define STATUS_INSIDE_HPP

#include "rectangle.hpp"


namespace UI::Windows::Status
{
    class Inside : public Rectangle
    {
    public:
        Inside(int height, int width, int begin_y, int begin_x);
    };
}



#endif
