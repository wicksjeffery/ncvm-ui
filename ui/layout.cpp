#include "layout.hpp"
#include "windows/rectangle.hpp"
#include "windows/background.hpp"
#include "windows/help.hpp"
#include "windows/options-selector.hpp"
#include "windows/options.hpp"

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
    // init_pair(2, COLOR_BLUE, COLOR_BLUE);
    // init_pair(3, COLOR_WHITE, COLOR_WHITE);
    // init_pair(4, COLOR_BLACK, COLOR_BLACK);
    // init_pair(5, COLOR_BLACK, COLOR_WHITE);
    // init_pair(6, COLOR_WHITE, COLOR_BLACK);
    // init_pair(7, COLOR_CYAN, COLOR_CYAN);
    // init_pair(8, COLOR_CYAN, COLOR_BLACK);
    // init_pair(9, COLOR_BLACK, COLOR_CYAN);
    // init_pair(10, COLOR_WHITE, COLOR_GREEN);
    // init_pair(11, COLOR_WHITE, COLOR_BLUE);
    // init_pair(12, COLOR_WHITE, COLOR_CYAN);
    // init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    // init_pair(14, COLOR_BLACK, COLOR_CYAN);
    // init_pair(15, COLOR_RED, COLOR_BLACK);
    // init_pair(16, COLOR_GREEN, COLOR_BLACK);
    // init_pair(17, COLOR_WHITE, COLOR_GREEN); //this one for vm is running
    // init_pair(18, COLOR_YELLOW, COLOR_GREEN);
    // init_pair(19, COLOR_BLACK, COLOR_WHITE); //TESTING
    // init_pair(20, COLOR_WHITE, COLOR_BLACK); //TESTING
    // init_pair(21, COLOR_WHITE, COLOR_BLACK); //TESTING
    // init_pair(22, COLOR_WHITE, COLOR_BLACK); //TESTING

    // //BEGIN Top (menu options) bar
    // attron(COLOR_PAIR(19));
    // mvhline(COLS-1, 1, ' ', LINES-1);
    // attroff(COLOR_PAIR(19));
    // //END Top (menu options) bar


//     menu_options = newwin(1, 4, 0, 1);
//     wbkgd(menu_options, COLOR_PAIR(19));
//     waddstr(menu_options, "menu");
//
//     wrefresh(menu_options);


    // using namespace Windows;
    // // using WR = const Rectangle*;
    // using WR = Rectangle*;
    //
    // all_windows.insert({"Background", static_cast<WR>
    //     (new Background(LINES, COLS, 0, 0) )} );
    //
    // all_windows.insert({"Help", static_cast<WR>
    //     (new Help(LINES-3, COLS-4, 2, 2) )} );
    //
    // all_windows.insert({"OptionsSelector", static_cast<WR>
    //     (new OptionsSelector(1, 9, 0, 0) )} );
    //
    // all_windows.insert({"Options", static_cast<WR>
    //     (new Options(20, 20, 1, 0) )} );

    Windows::Rectangle* ptr;

    ptr = new Windows::Background(LINES, COLS, 0, 0);
    all_windows.insert( {"Background", ptr} );
    ptr = new Windows::Help(LINES-3, COLS-4, 2, 2);
    all_windows.insert( {"Help", ptr} );
    ptr = new Windows::OptionsSelector(1, 9, 0, 0);
    all_windows.insert( {"OptionsSelector", ptr} );
    ptr = new Windows::Options(20, 20, 1, 0);
    all_windows.insert( {"Options", ptr} );

    update_panels();
    doupdate();

    // basePtr->hello();

    // auto options_selector = all_windows.find("OptionsSelector");
    // //
    // // // OptionsSelector* derivedPtr = dynamic_cast<OptionsSelector*>(options_selector->second);
    // // //
    // options_selector->second->hello();
    // getch();

}

UI::Layout::~Layout()
{
    for (auto const& [key, val] : all_windows)
    {
        delete val;
    }

    endwin();
}
