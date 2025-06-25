#include "layout.hpp"
#include "windows/collection.hpp"
#include "windows/rectangle.hpp"
#include "windows/background.hpp"
#include "windows/help.hpp"
#include "windows/options-selector.hpp"
#include "windows/options.hpp"
#include "windows/exit-selector.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
// #include <fstream>
#include <cxxabi.h>

UI::Layout::Layout(/*std::unordered_map<std::string, Windows::Rectangle*> all_windows*/)
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
    Rectangle* ptr;

    save(new Background(LINES, COLS, 0, 0));
    save(new Help(LINES-3, COLS-4, 2, 2));
    save(new OptionsSelector(1, 9, 0, 0));
    save(new Options(14, 15, 1, 0));
    save(new ExitSelector(1, 12, 12, 1));

    // ptr = new Windows::Background(LINES, COLS, 0, 0);
    // // // all_windows.insert( {"Background", ptr} );
    //
    // // ptr = new Windows::Help(LINES-3, COLS-4, 2, 2);
    // // all_windows.insert( {"Help", ptr} );
    // // ptr = new Windows::OptionsSelector(1, 9, 0, 0);
    // // all_windows.insert( {"OptionsSelector", ptr} );
    // // ptr = new Windows::Options(20, 20, 1, 0);
    // // all_windows.insert( {"Options", ptr} );

    update_panels();
    doupdate();
}

// std::ofstream outputFile;
void UI::Layout::save(Windows::Rectangle* w)
{
    // BEGIN extra code to shorten lines of code in window instantiation (in UI::Layout::Layout().
    int status = -1; // Status of the demangling operation
    char* window_name = abi::__cxa_demangle(typeid(*w).name(), nullptr, nullptr, &status);

    std::string child_class_name(window_name);
    if (status == 0)
    {
        // std::string temp = child_class_name.substr(child_class_name.find_first_not_of("UI::Windows::"));
        child_class_name = child_class_name.substr(child_class_name.find_first_not_of("UI::Windows::"));

        std::free(window_name);
    } else {
        throw("Name demangling failed");
    }
    // BEGIN extra code to shorten lines of code in window instantiation.


    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    // logger1.logMessage("First message from logger1.");
    collection.insert(child_class_name, w);

    // outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);
//     for (auto const& [key, value]: m_windows)
//     {
//         // printw("%s", key.c_str());
//
//
        // outputFile << "ok: " << collection.print() << std::flush;
//     }

    // outputFile << child_class_name << std::endl;
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
