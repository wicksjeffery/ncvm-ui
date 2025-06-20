#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <panel.h>

#include <iostream>

namespace UI::Windows
{
    class Rectangle
    {
    public:
        Rectangle();
        virtual ~Rectangle();

        Rectangle(int nlines, int ncols, int begin_y, int begin_x);


        WINDOW* get_window() const
        {
            return m_window;
        }

        PANEL* get_panel() const
        {
            return m_panel;
        }

        virtual void toggleSelected() { /*std::cout << '\a' << std::endl;*/}

        virtual void hello() const
        {
            std::cout << "Hello from Window." << std::endl;
        }

    protected:
        WINDOW* m_window;
        PANEL* m_panel;




    };
}

#endif
