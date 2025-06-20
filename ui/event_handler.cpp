#include "event_handler.hpp"
#include <iostream>

#include <curses.h>

UI::EventHandler::EventHandler(std::unordered_map<std::string, Windows::Rectangle*> &w)
    :
        m_windows(w)
{}


int UI::EventHandler::listen(int n)
{
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
                // std::string keysToSearch[] = {"Background", "Temp", "Nayhoo"};
                //
                // for (const std::string& key : keysToSearch) {
                //     auto it = myMap.find(key); // Use find() to search for the key
                //
                //     if (it != myMap.end()) {
                //         // Key found
                //         std::cout << "Key '" << key << "' found. Value: " << it->second << std::endl;
                //     } else {
                //         // Key not found
                //         std::cout << "Key '" << key << "' not found." << std::endl;
                //     }
                // }

                // auto rectangle = m_windows.find("Background");
                //
                // if (rectangle != m_windows.end())
                // {
                //     // Key found: rectangle->first, rectangle->second
                // } else
                // {
                //     // Key not found...
                //
                // }

                for (auto& [key, value]: m_windows)
                {
                    if (wenclose(value->get_window(), mouse_event.y, mouse_event.x) == true)
                    {
                        // //skip if not interested NOTE use panel_above(pan) instead maybe
                        // if (key == "Background")
                        // {
                        //     continue;
                        // }

                        if (key == "OptionsSelector")
                        {
                            // mvprintw(6, 6, "%s", key.c_str());
                            // mvprintw(6, 6, ":)");
                            // auto options_selector = m_windows.find("Options");

                            // show_panel(options_selector->second->get_panel());

                            value->toggleSelected();
                            // options_selector->second->hello();

                            update_panels();
                            doupdate();

                            break;
                        } else
                        {
                            // DEBUGGING STUFF:
                            // auto win = m_windows.find("Background");
                            // wattron(win->second->get_window(), COLOR_PAIR(5));
                            // mvwprintw(win->second->get_window(), 6, 25, "          ");
                            // mvwprintw(win->second->get_window(), 6, 25, "%s", key.c_str());
                            // wattroff(win->second->get_window(), COLOR_PAIR(5));
                            // wrefresh(win->second->get_window());

                            auto options_window = m_windows.find("Options");
                            hide_panel(options_window->second->get_panel());

                            update_panels();
                            doupdate();

                            break;
                        }

                    }
                }


                // if (wenclose(m_windows.front()->get_window(), mouse_event.y, mouse_event.x) == true)
                // {
                //     if (panel_hidden(m_windows.front()->get_panel()))
                //     {
                //         // mvwprintw(help_window, 6, 6, "%s", "panel_hidden");
                //         show_panel(m_windows.front()->get_panel());
                //     } else
                //     {
                //         hide_panel(m_windows.front()->get_panel());
                //     }
                //
                //     update_panels();
                //     doupdate();
                //
                //     // wrefresh(help_window);
                //     // exit_program = true;
                // }
            }
        }
    }
    return 1; //returning arbitrary value (not used yet)
}
