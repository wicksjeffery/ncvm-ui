#include "command-line-args.hpp"
#include "vm-monitor.hpp"
#include "layout.hpp"
// #include "vm-states.hpp"

// #include <thread>

#include <iostream>

// #include <getopt.h>

// // Write log data to logger_window. This can be relocated to inside Layout.
// void startLoggerWindow(WINDOW* logger_window)
// {
//     std::array<char, 128> buffer;
//
//     FILE* pipe = popen("journalctl -f", "r");
//
//     if (!pipe) throw std::runtime_error("popen() failed!");
//
//
//     while ((fgets(buffer.data(), buffer.size(), pipe) != NULL))
//     {
//             waddstr(logger_window, buffer.data());
//             wrefresh(logger_window);
//
//             sleep(1);
//     }
// }

int main(int argc, char* argv[])
{
    // try
    // {
    //     VMMonitor monitor;
    //     monitor.run(args.getPIDFileDir());
    // }
    // catch (const std::runtime_error& error)
    // {
    //     std::cerr << error.what() << std::endl;
    // }


    //
    // bool stop_vm_monitor = false;
    // std::thread monitor_vm_status(watch_vm_dir, &stop_vm_monitor, &vm_states);

    // Layout layout(vm_states);
    Layout layout;


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

