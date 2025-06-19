#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <panel.h>

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

    protected:
        WINDOW* m_window;
        PANEL* m_panel;

        virtual const char* hello() const
        {
            return "Hello from Window.";
        }
    };
}

#endif
