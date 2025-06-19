
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

        // Reference to the pointer to windows that's in layout.
        std::unordered_map<std::string, const Windows::Rectangle*> &m_windows;


    public:
        EventHandler(std::unordered_map<std::string, const Windows::Rectangle*> &w);

        int listen(int n);
    };
}



#endif
