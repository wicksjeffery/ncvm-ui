#ifndef OPTIONS_WINDOW_HPP
#define OPTIONS_WINDOW_HPP

#include "rectangle.hpp"


namespace UI::Windows
{
    class OptionsWindow : public Rectangle
    {
    public:
        OptionsWindow(int height, int width, int begin_y, int begin_x);

        void hello() const override
        {
            std::cout << "Hello from Options!! \a" << std::endl;
        }
    };
}



#endif
