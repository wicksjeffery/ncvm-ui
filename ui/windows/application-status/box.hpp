#ifndef APPLICATION_STATUS_INSIDE_HPP
#define APPLICATION_STATUS_INSIDE_HPP

#include "rectangle.hpp"


namespace UI::Windows::ApplicationStatus
{
    class Box: public Rectangle
    {
    public:
        Box(int height, int width, int begin_y, int begin_x);
    };
}



#endif
