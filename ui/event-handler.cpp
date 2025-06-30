#include "event-handler.hpp"
#include <iostream>
#include "windows/collection.hpp"
#include <curses.h>
#include <fstream>

// UI::EventHandler::EventHandler(std::unordered_map<std::string, Windows::Rectangle*> *w)
//     :
//         m_windows(*w)
// {
//         std::ofstream outputFile;
//         outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);
//         // // // for (auto [key, value]: *m_windows)
//         // // // {
//         // //
//         // //     // printw("%s", key.c_str());
//             auto it = m_windows.find("Help");
//         // //     // printw("%s", it->first.c_str());
//         // //
//             outputFile << it.&first << std::endl;
//         // // // }
//         // //
//         // //
//         // //
//         outputFile.close();
//
// }

void UI::EventHandler::toggleOptionsSelector(bool options_selector_was_clicked = false)
{
    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

    if ( panel_hidden(collection.find("OptionsWindow")->get_panel()) && options_selector_was_clicked)
    {
        show_panel(collection.find("OptionsWindow")->get_panel());
        show_panel(collection.find("About")->get_panel());
        show_panel(collection.find("Exit")->get_panel());
        collection.find("OptionsButton")->turnOnHighlighting();
    } else
    {
        hide_panel(collection.find("OptionsWindow")->get_panel());
        hide_panel(collection.find("About")->get_panel());
        hide_panel(collection.find("Exit")->get_panel());
        collection.find("OptionsButton")->turnOffHighlighting();
    }
}


int UI::EventHandler::listen(int n)
{
    std::ofstream outputFile;

    MEVENT mouse_event;

    while (exit_program == false)
    {
        int getch_return_value = getch();

        if (getch_return_value == KEY_MOUSE && getmouse(&mouse_event) == OK)
        {
            if (mouse_event.bstate & BUTTON1_RELEASED)
            {
                /*
                 * NOTE: GPM selection workaround:
                 *return 0; The left mouse button leaves selections highlighted,
                 * but sending a key clears the selection.
                 */

                std::cout << std::endl;
            }

            if (mouse_event.bstate & BUTTON2_PRESSED)
            {

                UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

                auto pair = collection.findWindow(mouse_event.y, mouse_event.x);

                if (pair.first != "")
                {
                    // // std::cout << "\a" << std::endl;
                    // wattron(collection.find("Background")->get_window(), COLOR_PAIR(3));
                    // mvwprintw(collection.find("Background")->get_window(), 1, 1, "You clicked:                       ");
                    // mvwprintw(collection.find("Background")->get_window(), 1, 1, "You clicked: %s", pair.first.c_str());
                    // wrefresh(collection.find("Background")->get_window());
                    // wattroff(collection.find("Background")->get_window(), COLOR_PAIR(3));

                    if (pair.first == "One")
                    {
                        wbkgd(collection.find("One")->get_window(), COLOR_PAIR(6));

                        wattron(collection.find("One")->get_window(), COLOR_PAIR(6));
                        mvwprintw(collection.find("One")->get_window(), 2, 3, "01234567890");
                        wattroff(collection.find("One")->get_window(), COLOR_PAIR(6));
                    }
                    else if (pair.first == "OptionsButton")
                    {
                        toggleOptionsSelector(true);
                    }
                    else if (pair.first == "About")
                    {
                        toggleOptionsSelector(true);

                        if (panel_hidden(collection.find("Information")->get_panel()))
                        {
                            show_panel(collection.find("Information")->get_panel());
                        }
                    }
                    else if (pair.first == "Exit")
                    {
                        // wattron(collection.find("Background")->get_window(), COLOR_PAIR(3));
                        // mvwprintw(collection.find("Background")->get_window(), 16, 25, "You clicked:                       ");
                        // mvwprintw(collection.find("Background")->get_window(), 16, 25, "You clicked: %s", pair.first.c_str());
                        // wattroff(collection.find("Background")->get_window(), COLOR_PAIR(3));

                        if (!panel_hidden(collection.find("Exit")->get_panel()))
                        {
                            exit_program = true;
                        }
                    }
                    else
                    {
                        // Close options window if it is open.
                        toggleOptionsSelector();
                    }
                }
                else
                {
                    // It shouldn't be possible to get here. Maybe throw instead?
                    mvwprintw(collection.find("Background")->get_window(), 6, 25, "EMPTY WINDOW");
                }

                update_panels();
                doupdate();
            }
        }
    }
    return 1; //returning arbitrary value (not used yet)
}
