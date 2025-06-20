#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include "rectangle.hpp"


namespace UI::Windows
{
    class Options : public Rectangle
    {
    public:
        Options(int height, int width, int begin_y, int begin_x);

        void hello() const override
        {
            std::cout << "Hello from Options!! \a" << std::endl;
        }
    };
}



#endif
