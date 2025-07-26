#include "event-handler.hpp"
#include <iostream>
#include "windows/collection.hpp"
#include "../vm/manager.hpp"
#include <curses.h>
#include <fstream>
#include <thread>

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

    if ( panel_hidden(collection.find("UI::Windows::OptionsWindow")->get_panel()) && options_selector_was_clicked)
    {
        show_panel(collection.find("UI::Windows::OptionsWindow")->get_panel());
        show_panel(collection.find("UI::Windows::MenuItems::About")->get_panel());
        show_panel(collection.find("UI::Windows::MenuItems::Exit")->get_panel());
        collection.find("UI::Windows::OptionsButton")->turnOnHighlighting();
    } else
    {
        hide_panel(collection.find("UI::Windows::OptionsWindow")->get_panel());
        hide_panel(collection.find("UI::Windows::MenuItems::About")->get_panel());
        hide_panel(collection.find("UI::Windows::MenuItems::Exit")->get_panel());
        collection.find("UI::Windows::OptionsButton")->turnOffHighlighting();
    }
}


int UI::EventHandler::listen(int n)
{
    // VM::Manager vmm;

    // std::ofstream f("/tmp/foo1", std::fstream::trunc);
    //
    // f << "okpeT: " << std::hex << std::this_thread::get_id() << std::endl;
    // f.close();
    // std::cout << "\a";

    MEVENT mouse_event;

    while (exit_program == false)
    {
        // vmm.monitorStates();

        int getch_return_value = getch();

        if (getch_return_value == KEY_MOUSE && getmouse(&mouse_event) == OK)
        {
            if (mouse_event.bstate & BUTTON1_RELEASED)
            {
                /*
                 * NOTE: GPM selection workaround:
                 * The left mouse button leaves selections highlighted.
                 */

                std::cout << std::endl;
                std::cout << '\a' << std::flush;
                clearok(stdscr, TRUE);
                update_panels();
                doupdate();
            }

            if (mouse_event.bstate & BUTTON2_PRESSED)
            {
                // std::cout << "\a" << std::endl;
                UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

                auto pair = collection.findWindow(mouse_event.y, mouse_event.x);

                if (pair.first != "")
                {
                    // std::cout << "\a" << std::endl;
                    //     // redrawwin(stdscr);
                    // clear();
                    // refresh(); // Clears mouse-paste that can happen from the middle button - screws up the screen.
                    //
                    //     // redrawwin();
                    // wattron(collection.find("ApplicationStatus::Box")->get_window(), COLOR_PAIR(3));
                    // // wprintw(collection.find("ApplicationStatus::Box")->get_window(), "You clicked:                       ");
                    mvwprintw(collection.find("UI::Windows::VMControl::One")->get_window(), 0, 0, "%s", pair.first.c_str());
                    // wrefresh(collection.find("ApplicationStatus::Box")->get_window());
                    // wattroff(collection.find("ApplicationStatus::Box")->get_window(), COLOR_PAIR(3));

                    if (pair.first == "UI::Windows::VMControl::One")
                    {
                        // std::cout << "\a" << std::endl;
                        // wattron(collection.find("UI::Windows::Status::Inside")->get_window(), COLOR_PAIR(3));
                        // mvwprintw(collection.find("UI::Windows::Status::Inside")->get_window(), 1, 1, "You clicked:                       ");
                        // mvwprintw(collection.find("UI::Windows::Status::Inside")->get_window(), 1, 1, "You clicked: %s", pair.first.c_str());
                        // wrefresh(collection.find("UI::Windows::Status::Inside")->get_window());
                        // wattroff(collection.find("UI::Windows::Status::Inside")->get_window(), COLOR_PAIR(3));
                        // wrefresh(collection.find("UI::Windows::Status::Inside")->get_window());
                    }
                    else if (pair.first == "UI::Windows::OptionsButton")
                    {
                        toggleOptionsSelector(true);
                    }
                    else if (pair.first == "UI::Windows::MenuItems::About")
                    {
                        toggleOptionsSelector(true);

                        if (panel_hidden(collection.find("UI::Windows::Information")->get_panel()))
                        {
                            show_panel(collection.find("UI::Windows::Information")->get_panel());
                        }
                    }
                    else if (pair.first == "UI::Windows::MenuItems::Exit")
                    {
                        // wattron(collection.find("Background")->get_window(), COLOR_PAIR(3));
                        // mvwprintw(collection.find("Background")->get_window(), 16, 25, "You clicked:                       ");
                        // mvwprintw(collection.find("Background")->get_window(), LINES-1, 0, "You clicked: %s", pair.first.c_str());
                        // wrefresh(collection.find("UI::Windows::Status::Inside")->get_window());
                        // wattroff(collection.find("Background")->get_window(), COLOR_PAIR(3));

                        if (!panel_hidden(collection.find("UI::Windows::MenuItems::Exit")->get_panel()))
                        {
                            // exit_program = true;
                            return 0;
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
                    mvwprintw(collection.find("UI::Windows::Background")->get_window(), 6, 25, "EMPTY WINDOW");
                }

                update_panels();
                doupdate();
            }
            // else
            // {
            //     // redrawwin(stdscr);
            //     clear();
            //     refresh();
            //
            //     // redrawwin();
            // }
        }
    }
    return 1; //returning arbitrary value (not used yet)
}
