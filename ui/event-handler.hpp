
#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

// #include <curses.h>

#include "windows/rectangle.hpp"
#include <unordered_map>
#include <string>
#include "../ui/windows/primary/stdscr.hpp"

namespace UI
{
    class EventHandler
    {
        bool exit_program = false;

        void toggleOptionsSelector(bool options_selector_was_clicked);

        // UI::Windows::Primary::Stdscr* scrn;

    public:
        // EventHandler(UI::Windows::Primary::Stdscr* scr) : scrn(scr){;}
        // EventHandler();

        int listenOLD(int n);
        int listen(int n);
    };
}



#endif

