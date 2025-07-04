#ifndef STATUS_HPP
#define STATUS_HPP

#include "rectangle.hpp"


namespace UI::Windows::Status
{
    class OutterFrame : public Rectangle
    {
    public:
        OutterFrame(int height, int width, int begin_y, int begin_x);

        // void hello() const override
        // {
        //     std::cout << "Hello from Options!! \a" << std::endl;
        // }
    };
}



#endif
