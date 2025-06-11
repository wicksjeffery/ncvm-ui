#include "layout.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include <future>

int main(/*int argc, char* argv[]*/)
{
    Layout layout;
    // layout.handleMouseEvents;
    // std::thread t1(&Layout::handleMouseEvents, &layout, 9);
    auto f1 = std::async(&Layout::handleMouseEvents, &layout, 9);

    if (f1.get() == 0)
    {
        return 0;
    } else return 1;

    // std::cout << "hello: " << std::endl;
    // // auto res1 = f1.get();
    // int b = 0;
    // while (b != 5)
    // {
    //     b = f1.get();
    //     std::cout << "\a" << std::flush;
    //     std::cout << "main: " << b << std::endl;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    // t1.join();

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



    // int number;
    // std::cout << "Enter an integer: ";
    // std::cin >> number;
    // std::cout << "You entered: " << number << std::endl;

    // t1.join(); // Don't exit program until t1 finishes.


    return 0;
}

