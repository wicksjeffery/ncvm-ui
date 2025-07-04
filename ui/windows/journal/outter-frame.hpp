#ifndef STATUS_OUTTERFRAME_HPP
#define STATUS_OUTTERFRAME_HPP

#include "rectangle.hpp"


namespace UI::Windows::Journal
{
    class OutterFrame : public Rectangle
    {
    public:
        OutterFrame(int height, int width, int begin_y, int begin_x);
    };
}



#endif
