#include "layout.hpp"
#include "windows/collection.hpp"
#include "windows/rectangle.hpp"
#include "windows/background.hpp"
#include "windows/information.hpp"
#include "windows/options-button.hpp"
#include "windows/options-menu/options-window.hpp"
#include "windows/options-menu/about.hpp"
#include "windows/options-menu/exit.hpp"

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
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_RELEASED | BUTTON2_PRESSED, NULL);

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);



    using namespace Windows;
    using namespace MenuItems;

    save(new Background(LINES, COLS, 0, 0));
    save(new Information(LINES-3, COLS-4, 2, 2));
    save(new OptionsButton(1, 9, 0, 0));
    save(new OptionsWindow(14, 15, 1, 0));
    save(new Exit(1, 12, 10, 1));
    save(new About(1, 12, 12, 1));


    update_panels();
    doupdate();
}

std::ofstream outputFile;
void UI::Layout::save(Windows::Rectangle* w)
{
    // outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);

    // BEGIN extra code to shorten lines of code in window instantiation (in UI::Layout::Layout().
    int status = -1; // Status of the demangling operation
    char* window_name = abi::__cxa_demangle(typeid(*w).name(), nullptr, nullptr, &status);

    std::string child_class_name(window_name);
    if (status == 0)
    {
        std::string mask("UI::Windows::");

        if (child_class_name.find("UI::Windows::MenuItems::")  != std::string::npos)
        {
            mask = "UI::Windows::MenuItems::";
        }

        // outputFile << child_class_name.substr(mask.length()) << std::endl;
        child_class_name = child_class_name.substr(mask.length());


        std::free(window_name);
    } else {
        throw std::runtime_error("Name demangling failed");
    }
    // BEGIN extra code to shorten lines of code in window instantiation.


    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    // logger1.logMessage("First message from logger1.");
    collection.insert(child_class_name, w);


//     for (auto const& [key, value]: m_windows)
//     {
//         // printw("%s", key.c_str());
//
//

//     }


    // outputFile.close();

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
