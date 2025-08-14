#include "button1-released.hpp"
// #include "../ui/windows/primary"
#include "../ui/windows/primary/stdscr.hpp"
#include <panel.h>
// #include <iostream>
// #include "windows/collection.hpp"
// #include "../vm/manager.hpp"
// #include <curses.h>
// #include <fstream>
// #include <thread>

UI::Button1Released::Button1Released(MEVENT mouse_event)
{
    // IAMHERE
    //TODO make Stdscr a singleton and invoke it here, so I know
    // the X Y positions of the VM windows.

    UI::Windows::Primary::Stdscr& stdscreen = UI::Windows::Primary::Stdscr::getInstance();





    // stdscreen.writeToUI(vms[vm_number].name,
    //                     // vms[vm_number].state,
    //                     initialStateToString(vms[vm_number].state),
    //                     vms[vm_number].reason,
    //                     vm_number,
    //                     true);


    // if (mouse_event.y == 0 && mouse_event.x > 0 && mouse_event.x < 8)
    if (mouse_event.y > 3 && mouse_event.y < 7)
    {

        //
        // // attron(COLOR_PAIR(5));
        // // mvprintw(1, 0, "  ");
        // // mvprintw(1, 0, "%d", mouse_event.x);
        // // attroff(COLOR_PAIR(5));
        // // refresh();

        if (mouse_event.x > stdscreen.getVMwindowStartX(0) && mouse_event.x < ( stdscreen.getVMwindowStartX(0)+(17-1) )) //TODO use a const from a header instead of "17"
        {
            attron(COLOR_PAIR(8));

            // mvprintw(1, 0, "%s", "helloer:");
            printw("%s", "helloer:");
            // mvprintw(1, 1, "%s%d", "helloer: ", stdscreen.getVMwindowStartX(0));
            // refresh();
            update_panels();
            doupdate();

            stdscreen.setVMBoxColor(0);
            attroff(COLOR_PAIR(8));


        }
    }
}

