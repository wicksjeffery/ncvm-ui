#include "layout.hpp"

#include <iostream>

int main(/*int argc, char* argv[]*/)
{
    Layout layout;
    layout.test();


    // sleep(15);
    // stop_vm_monitor = true;
    // monitor_vm_status.join();


    // WINDOW* lw = layout.getLoggerWindow();

    // std::thread (startLoggerWindow, lw).detach();

    // initscr();
    // cbreak();
    // curs_set(0);
    // timeout(300);
    //
    // keypad(stdscr, TRUE); // For mouse events.
    // mousemask(BUTTON3_RELEASED | BUTTON2_RELEASED | BUTTON1_PRESSED | BUTTON1_RELEASED, NULL);
    //
    // while (true)
    // {
    //     // usleep(300);
    //     // layout.updateVMStatus(vm_states); // maybe add a delay in this function
    //
    //     int getch_return_value = getch();
    //
    //     if (getch_return_value == KEY_MOUSE)
    //     {
    //         printw("poot sqwok\n");
    //         refresh();
    //
    //         // MEVENT mouse_event;
    //         //
    //         // if (getmouse(&mouse_event) == OK)
    //         // {
    //         //     layout.handleEvents(mouse_event);
    //         // }
    //     }
    // }


    return 0;
}

