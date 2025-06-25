
#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

// #include <curses.h>

#include "windows/rectangle.hpp"
#include <unordered_map>
#include <string>

namespace UI
{
    class EventHandler
    {
        bool exit_program = false;

        void toggleOptionsSelector(bool options_selector_was_clicked);

    public:
        int listen(int n);
    };
}



#endif
