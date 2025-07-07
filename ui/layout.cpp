#include "layout.hpp"
#include "windows/collection.hpp"
#include "windows/rectangle.hpp"
#include "windows/background.hpp"
#include "windows/information.hpp"
#include "windows/vm-control/vm-outter-frame.hpp"
#include "windows/vm-control/one.hpp"
#include "windows/vm-control/two.hpp"
#include "windows/vm-control/three.hpp"
#include "windows/vm-control/four.hpp"
#include "windows/options-button.hpp"
#include "windows/options-menu/options-window.hpp"
#include "windows/options-menu/about.hpp"
#include "windows/options-menu/exit.hpp"
#include "windows/journal/outter-frame.hpp"
#include "windows/journal/inside.hpp"
#include "windows/status/outter-frame.hpp"
#include "windows/status/inside.hpp"

#include "../logging/manager.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <fstream>
#include <cxxabi.h>

#include <stdexcept>


UI::Layout::Layout()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    scrollok(stdscr, false);
    clearok(stdscr, false);
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_RELEASED | BUTTON2_PRESSED, NULL);

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);



    using namespace Windows;
    // using namespace MenuItems;
    // using namespace VMControl;
    // using namespace Status;
    // using namespace Journal;

    // BEGIN: setup for vm windows
    // std::ofstream outputFile("/tmp/debug.txt");
    // outputFile << "Space needed: " << 17 * 4 << std::endl;
    short available_space = (COLS-5) - 4;
    // short available_space = (100-5) - 4;
    // outputFile << "Available space is: " << available_space << std::endl;
    short min_space_needed = 17 * 4;
    // outputFile << "Min space needed: " << min_space_needed << std::endl;
    short spaces_left_over = available_space - min_space_needed;
    // outputFile << "Space left over: " << spaces_left_over << std::endl;
    short available_spaces_leftover = spaces_left_over / 5;
    // outputFile << "Spaces distributed: " << available_spaces_leftover << std::endl;
    short leftovers_from_distributed = min_space_needed % 5; // There are 5 total spaces.
    // outputFile << "Leftover from spaces distributed: " << leftovers_from_distributed << std::endl;

    if (available_space < min_space_needed)
    {
        throw(std::runtime_error("Error: The mimimum is 80 columns wide and 30 lines high. (640x480)"));
    }

    short first_vm_start_x = 0;
    short second_vm_start_x = 0;
    short third_vm_start_x = 0;
    short fourth_vm_start_x = 0;

    // Distrubute leftover spaces
    switch (leftovers_from_distributed)
    {
        case 1:
            // Put it in the middle.
            third_vm_start_x = 1;
            break;
        case 2:
            // Put them on the ends.
            first_vm_start_x = 1;
            // fourth is granted.
            break;
        case 3:
            // Put them in the middle and ends
            first_vm_start_x = 1;
            third_vm_start_x = 1;
            break;
        case 4:
            // Put on all except middle.
            first_vm_start_x = 1;
            second_vm_start_x = 1;
            fourth_vm_start_x = 1;
            break;
    }

    const unsigned vm_box_width = 17;//constant
    first_vm_start_x += 4 + available_spaces_leftover;
    second_vm_start_x += (vm_box_width + first_vm_start_x + available_spaces_leftover);
    third_vm_start_x += (vm_box_width + second_vm_start_x + available_spaces_leftover);
    fourth_vm_start_x += (vm_box_width + third_vm_start_x + available_spaces_leftover);

    // END: setup for vm windows



    // outputFile.close();

    save(new Background(LINES, COLS, 0, 0));
    save(new VMControl::VMOutterFrame(8, COLS-4, 2, 2));
    save(new VMControl::One(first_vm_start_x));
    save(new VMControl::Two(second_vm_start_x));
    save(new VMControl::Three(third_vm_start_x));
    save(new VMControl::Four(fourth_vm_start_x));
    save(new Information(LINES-3, COLS-4, 2, 2));
    save(new OptionsButton(1, 9, 0, 0));
    save(new OptionsWindow(14, 15, 1, 0));
    save(new MenuItems::Exit(1, 12, 10, 1));
    save(new MenuItems::About(1, 12, 12, 1));
    save(new Journal::OutterFrame(LINES-20, COLS-4, 11, 2));
    save(new Journal::Inside(LINES-23, COLS-11, 12, 5));
    save(new Status::OutterFrame(7, COLS-4, LINES-8, 2));
    save(new Status::Inside(4, COLS-11, LINES-7, 5)); //TODO leave the namespace for clarity.


    // UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    // //
    // wattron(collection.find("One")->get_window(), COLOR_PAIR(3));
    // box(collection.find("One")->get_window(), 0, 0),
    // mvwprintw(collection.find("One")->get_window(),
              // 2,
              // 3, "01234567890");
    // wattroff(collection.find("One")->get_window(), COLOR_PAIR(3));
    // wattron(collection.find("Two")->get_window(), COLOR_PAIR(3));
    // box(collection.find("Two")->get_window(), 0, 0),
    // wattron(collection.find("Three")->get_window(), COLOR_PAIR(3));
    // box(collection.find("Three")->get_window(), 0, 0),
    // wattron(collection.find("Four")->get_window(), COLOR_PAIR(3));
    // box(collection.find("Four")->get_window(), 0, 0),
    //
    // wattron(collection.find("Background")->get_window(), COLOR_PAIR(3));
    // mvwprintw(collection.find("Background")->get_window(),
    //           9,
    //           COLS-5, "QRXYZ");
    // collection.printAll();

    // mvwprintw(collection.find("One")->get_window(),
    //           1,
    //           14, "1");
    // // mvwprintw(collection.find("VMOutterFrame")->get_window(),
    //           // 1,
    //           // second_vm_start_x, "2");
    // wattroff(collection.find("One")->get_window(), COLOR_PAIR(3));
    // wrefresh(collection.find("One")->get_window());

    // wattron(collection.find("VMOutterFrame")->get_window(), COLOR_PAIR(5));
    // mvwprintw(collection.find("VMOutterFrame")->get_window(),
              // 1,
              // 4, "012345678901");
    // wattroff(collection.find("VMOutterFrame")->get_window(), COLOR_PAIR(3));



    // Announce to logging that all the windows are created.
    // Logger& logger = Logger::getInstance(); //TODO write to application log that ncvm-ui is started.
    // Logger::getInstance();
    // logger.write("key");

    // Uncomment to see what's in the collection:
    // UI::Windows::Collection::getInstance().printAll();

    update_panels();
    doupdate();
}

void UI::Layout::save(Windows::Rectangle* w)
{
    std::ofstream outputFile;
    // if (dont_save == true) return; // Don't save windows that aren't selectable.
    outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);

    // BEGIN extra code to shorten lines of code in window instantiation (in UI::Layout::Layout().
    int status = -1; // Status of the demangling operation
    char* window_name = abi::__cxa_demangle(typeid(*w).name(), nullptr, nullptr, &status);

    std::string child_class_name(window_name);
    // outputFile << child_class_name << std::endl;
    if (status == 0)
    {
        // std::string mask("UI::Windows::");

        // if (child_class_name.find("UI::Windows::MenuItems::")  != std::string::npos)
        // {
        //     mask = "UI::Windows::MenuItems::";
        // }
        // if (child_class_name.find("UI::Windows::VMControl::")  != std::string::npos)
        // {
        //     mask = "UI::Windows::VMControl::";
        // }
        // if (child_class_name.find("UI::Windows::Status::")  != std::string::npos)
        // {
        //     mask = "UI::Windows::Status::";
        // }
        // if (child_class_name.find("UI::Windows::Journal::")  != std::string::npos)
        // {
        //     mask = "UI::Windows::Journal::";
        // }

        // child_class_name = child_class_name.substr(mask.length());
        // outputFile << child_class_name << std::endl;


        std::free(window_name);
    } else {
        throw std::runtime_error("Name demangling failed");
    }
    // BEGIN extra code to shorten lines of code in window instantiation.

    outputFile << child_class_name << std::endl;
    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    // logger1.logMessage("First message from logger1.");
    collection.insert(child_class_name, w);


//     for (auto const& [key, value]: m_windows)
//     {
//         // printw("%s", key.c_str());
//
//

//     }


    outputFile.close();

    // collection.printAll();
}

UI::Layout::~Layout()
{
    // for (auto const& [key, val] : all_windows)
    // {
    //     delete val;
    // }

    endwin();
}
