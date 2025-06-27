#ifndef VM_OUTTER_FRAME_HPP
#define VM_OUTTER_FRAME_HPP

#include "rectangle.hpp"


namespace UI::Windows::VMControl
{
    class VMOutterFrame : public Rectangle
    {
    public:
        VMOutterFrame(int height, int width, int begin_y, int begin_x);
    };
}



#endif
