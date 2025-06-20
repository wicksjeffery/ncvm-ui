#ifndef OPTONS_SELECTOR_HPP
#define OPTONS_SELECTOR_HPP

#include "rectangle.hpp"


namespace UI::Windows
{
    class OptionsSelector : public Rectangle
    {
    public:
        OptionsSelector(int height, int width, int begin_y, int begin_x);

        void toggleSelected() override;

        void hello() const override
        {
            std::cout << "Hello from OptionsSelector. \a" << std::endl;
        }
    };
}



#endif
