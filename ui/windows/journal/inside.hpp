#ifndef JOURNAL_INSIDE_HPP
#define JOURNAL_INSIDE_HPP

#include "rectangle.hpp"


namespace UI::Windows::Journal
{
    class Inside : public Rectangle
    {
    public:
        Inside(int height, int width, int begin_y, int begin_x);
    };
}



#endif
