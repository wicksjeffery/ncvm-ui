#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "rectangle.hpp"

#include <string>
#include <unordered_map>


namespace UI
{
    class Layout
    {
        void save(Windows::Rectangle* w);
    public:
        Layout();
        ~Layout();
    };
}
#endif
