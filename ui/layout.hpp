#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "rectangle.hpp"

#include <string>
#include <unordered_map>
#include "windows/primary/stdscr.hpp"


namespace UI
{
    class Layout
    {
        void save(Windows::Rectangle* w);

        Windows::Primary::Stdscr* scrn;

    public:
        Layout();
        ~Layout();

        Windows::Primary::Stdscr* getSTDscreen() {return scrn;}
    };
}
#endif
