#ifndef OPTONS_BUTTON_HPP
#define OPTONS_BUTTON_HPP

#include "rectangle.hpp"


namespace UI::Windows
{
    class OptionsButton : public Rectangle
    {
    public:
        OptionsButton(int height, int width, int begin_y, int begin_x);

        void toggleHighlighting() override;
        void turnOnHighlighting() override;
        void turnOffHighlighting() override;

        void hello() const override
        {
            std::cout << "Hello from OptionsSelector. \a" << std::endl;
        }
    };
}



#endif
