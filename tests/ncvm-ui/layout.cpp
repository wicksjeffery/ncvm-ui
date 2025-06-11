#include "layout.hpp"

// #include <string.h>
#include <thread>
#include <iostream>



// Layout::Layout(VmStates vm_states)
Layout::Layout()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    mousemask(BUTTON3_RELEASED | BUTTON2_PRESSED | BUTTON2_RELEASED | BUTTON1_PRESSED | BUTTON1_RELEASED, NULL);
    start_color();
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_CYAN);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    init_pair(9, COLOR_BLACK, COLOR_CYAN);
    // init_pair(10, COLOR_WHITE, COLOR_GREEN);
    init_pair(11, COLOR_WHITE, COLOR_BLUE);
    init_pair(12, COLOR_WHITE, COLOR_CYAN);
    init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    init_pair(14, COLOR_BLACK, COLOR_CYAN);
    init_pair(15, COLOR_RED, COLOR_BLACK);
    init_pair(16, COLOR_GREEN, COLOR_BLACK);
    init_pair(17, COLOR_WHITE, COLOR_GREEN); //this one for vm is running
    init_pair(18, COLOR_YELLOW, COLOR_GREEN);
    init_pair(19, COLOR_BLACK, COLOR_WHITE); //TESTING


    wbkgd(stdscr,COLOR_PAIR(2));

    refresh();
    //
    createToolBar();
    // create_outter_machines_window();
    // create_logger_window();
    //
    // options_is_selected = false;
    // GoldLinux_is_selected = false;
    // GoldWin10_is_selected = false;
    // SilverWin_is_selected = false;



    createHelpWindow("This is the help text.");
    help_panel = new_panel(help_window); 	/* Push 0, order: stdscr-0 */
    // help_panel_data.hide = false;
    set_panel_userptr(help_panel, &help_panel_data);

    update_panels();
    doupdate();
}

Layout::~Layout()
{
        // t1.join();
    endwin();
}

void Layout::createHelpWindow(const char* help_text)
{
    help_window = newwin(LINES-4, COLS-5, 2, 2);

    wattron(help_window, COLOR_PAIR(3) | A_BOLD);
    box(help_window, 0, 0);
    wattroff(help_window, COLOR_PAIR(3) | A_BOLD);

    // BEGIN: give the box a "shadow"
    attron(COLOR_PAIR(4));
    //Right
    move(3, COLS-3);
    vline(' ', LINES-4);

    //Bottom
    move(LINES-2, 3);
    hline(' ', COLS-6);

    attroff(COLOR_PAIR(4));
    // END: give the box a "shadow"

    mvwprintw(help_window, 1, 1, "%s", help_text);

    wbkgd(help_window, COLOR_PAIR(19));
}

void Layout::createToolBar()
{
    //BEGIN Top bar
    attron(COLOR_PAIR(19));
    move(0, 0);
    hline(' ', COLS);

    attroff(COLOR_PAIR(19));
    refresh();
    //END Top bar

    menu_options = newwin(1, 4, 0, 1);
    wbkgd(menu_options, COLOR_PAIR(19));
    waddstr(menu_options, "menu");

    wrefresh(menu_options);
}

// void Layout::drawVMBox(int horizontal_position, std::string vm_name, bool vm_is_running)
// {
//     // // The left vm box:
//     // WINDOW* outter_box_border = subwin(machines_window, 5, 17, 3, horizontal_position);
//     // box(outter_box_border, 0 , 0);
//     // wbkgd(outter_box_border, COLOR_PAIR(5));
//     //
//     // WINDOW* vm_text_window = subwin(outter_box_border, 3, 13, 4, horizontal_position + 2);
//     //
//     // if (vm_is_running) wbkgd(vm_text_window, COLOR_PAIR(17) | A_BOLD);
//     // else wbkgd(vm_text_window, COLOR_PAIR(6) | A_BOLD);
//     //
//     // mvwaddstr(vm_text_window, 1, 2, vm_name.c_str());
//     //
//     // if (vm_name == "GoldLinux") GoldLinuxWindow = vm_text_window;
//     // if (vm_name == "GoldWin10") GoldWin10Window = vm_text_window;
//     // if (vm_name == "SilverWin") SilverWinWindow = vm_text_window;
//     // //if (vm_name == "GoldLinux") EmptyWindow = vm_text_window;
//     //
//     // wrefresh(outter_box_border);
// }
//
// void Layout::create_outter_machines_window()
// {
//     // // BEGIN: Make outter box
//     // machines_window = newwin(7, COLS-4, 2, 2);
//     // box(machines_window, 0 , 0);
//     // wbkgd(machines_window,COLOR_PAIR(3) | A_BOLD);
//     // wrefresh(machines_window);
//     //
//     // // BEGIN: give the box a "shadow"
//     // attron(COLOR_PAIR(4));
//     // move(9, 3);
//     // hline(' ', COLS-4);
//     // move(3, COLS-2);
//     // vline(' ', 6);
//     // attroff(COLOR_PAIR(4));
//     // refresh();
//     // END: give the box a "shadow"
//     // END: Make outter box
//
//     // // BEGIN: Make inner boxes and add the vm names
//     // int text_box_left_horizontal_position = 4;
//     // int text_box_left_center_horizontal_position = (COLS / 2) - 18;
//     // int text_box_right_center_horizontal_position = (COLS / 2) + 1;
//     // int text_box_right_horizontal_position = COLS - 21;
//     //
//     // drawVMBox(text_box_left_horizontal_position, "GoldLinux", m_vm_states.GoldLinux_is_running);
//     // drawVMBox(text_box_left_center_horizontal_position, "GoldWin10", m_vm_states.GoldWin10_is_running);
//     // drawVMBox(text_box_right_center_horizontal_position, "SilverWin", m_vm_states.SilverWin_is_running);
//     // drawVMBox(text_box_right_horizontal_position, "--EMPTY--", false);
//     // // END: Make inner boxes and add the vm names
//
//     // create_inner_machines_boxes();
// }
//
// void Layout::create_inner_machines_boxes()
// {
//     // // BEGIN: Make inner boxes and add the vm names
//     // int text_box_left_horizontal_position = 4;
//     // int text_box_left_center_horizontal_position = (COLS / 2) - 18;
//     // int text_box_right_center_horizontal_position = (COLS / 2) + 1;
//     // int text_box_right_horizontal_position = COLS - 21;
//
//     // drawVMBox(text_box_left_horizontal_position, "GoldLinux", m_vm_states.GoldLinux_is_running);
//     // drawVMBox(text_box_left_center_horizontal_position, "GoldWin10", m_vm_states.GoldWin10_is_running);
//     // drawVMBox(text_box_right_center_horizontal_position, "SilverWin", m_vm_states.SilverWin_is_running);
//     // drawVMBox(text_box_right_horizontal_position, "--EMPTY--", false);
//     // END: Make inner boxes and add the vm names
// }
//
// void Layout::create_logger_window()
// {
//
//     // WINDOW* logger_window_border = newwin(LINES-13, COLS-4, 11, 2);
//     // box(logger_window_border, 0 , 0);// 0, 0 gives default characters for the lines
//     // wbkgd(logger_window_border,COLOR_PAIR(3) | A_BOLD);
//     // wrefresh(logger_window_border);
//     //
//     // // BEGIN: give the box a "shadow"
//     // attron(COLOR_PAIR(4));
//     // move(LINES-2, 3);
//     // hline(' ', COLS-4);
//     // move(12, COLS-2);
//     // vline(' ', LINES-13);
//     // attroff(COLOR_PAIR(4));
//     // refresh();
//     // // END: give the box a "shadow"
//     //
//     // logger_window = subwin(logger_window_border, LINES-15, COLS-8, 12, 4);
//     //
//     // wattron(logger_window, COLOR_PAIR(5) | A_DIM);
//     //
//     // scrollok(logger_window, TRUE);
//     //
//     // wrefresh(logger_window_border);
//     // wrefresh(logger_window);
// }
//
// // void Layout::updateVMStatus(VmStates vm_states)
// // {
//     // // if (m_vm_states.GoldLinux_is_running != vm_states.GoldLinux_is_running)
//     // if (true) //commented the above to get complining
//     // {
//     //     // if (vm_states.GoldLinux_is_running)
//     //     if (true) //commented the above to get complining
//     //     {
//     //         wborder(GoldLinuxWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //         wbkgd(GoldLinuxWindow, COLOR_PAIR(17) | A_BOLD);
//     //         wrefresh(GoldLinuxWindow);
//     //     }
//     //     else
//     //     {
//     //         wbkgd(GoldLinuxWindow, COLOR_PAIR(6) | A_BOLD);
//     //         wrefresh(GoldLinuxWindow);
//     //     }
//     //
//     //     m_vm_states = vm_states;
//     // }
//     //
//     // // if (m_vm_states.GoldWin10_is_running != vm_states.GoldWin10_is_running)
//     // if (ture) //commented the above to get complining
//     // {
//     //     if (vm_states.GoldWin10_is_running)
//     //     {
//     //         wborder(GoldWin10Window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //         wbkgd(GoldWin10Window, COLOR_PAIR(17) | A_BOLD);
//     //         wrefresh(GoldWin10Window);
//     //     }
//     //     if (!vm_states.GoldWin10_is_running)
//     //     {
//     //         wbkgd(GoldWin10Window, COLOR_PAIR(6) | A_BOLD);
//     //         wrefresh(GoldWin10Window);
//     //     }
//     //
//     //     m_vm_states = vm_states;
//     // }
//     //
//     // if (m_vm_states.SilverWin_is_running != vm_states.SilverWin_is_running)
//     // {
//     //     if (vm_states.SilverWin_is_running)
//     //     {
//     //         wborder(SilverWinWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //         wbkgd(SilverWinWindow, COLOR_PAIR(17) | A_BOLD);
//     //         wrefresh(SilverWinWindow);
//     //     }
//     //
//     //     if (!vm_states.SilverWin_is_running)
//     //     {
//     //         //wborder(SilverWinWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //         wbkgd(SilverWinWindow, COLOR_PAIR(6) | A_BOLD);
//     //         wrefresh(SilverWinWindow);
//     //     }
//     //
//     //     m_vm_states = vm_states;
//     // }
// // }
//
// WINDOW* Layout::getLoggerWindow()
// {
//     return logger_window;
// }
//
//
// void Layout::deselectBox(std::string vm_name)
// {
//     // sleep(2);
//     //
//     // if (vm_name == "GoldLinux" && m_vm_states.GoldLinux_is_running == false)
//     // {
//     //     wborder(GoldLinuxWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //     wbkgd(GoldLinuxWindow, COLOR_PAIR(6) | A_BOLD);
//     //     wrefresh(GoldLinuxWindow);
//     //
//     //     GoldLinux_is_selected = false;
//     // }
//     // else if (vm_name == "GoldWin10" && m_vm_states.GoldWin10_is_running == false)
//     // {
//     //     wborder(GoldWin10Window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //     wbkgd(GoldWin10Window, COLOR_PAIR(6) | A_BOLD);
//     //     wrefresh(GoldWin10Window);
//     //
//     //     GoldWin10_is_selected = false;
//     // }
//     // else if (vm_name == "SilverWin" && m_vm_states.SilverWin_is_running == false)
//     // {
//     //     wborder(SilverWinWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//     //     wbkgd(SilverWinWindow, COLOR_PAIR(6) | A_BOLD);
//     //     wrefresh(SilverWinWindow);
//     //
//     //     SilverWin_is_selected = false;
//     // }
// }
//
//

int Layout::handleMouseEvents(int n)
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
                * The left mouse button leaves selections highlighted,
                * but sending a key clears the selection.
                */

                std::cout << std::endl;
            }

            if (mouse_event.bstate & BUTTON2_PRESSED)
            {
                if (wenclose(menu_options, mouse_event.y, mouse_event.x) == true)
                {
                    mvwprintw(help_window, 5, 5, "%s", "BUTTON2_PRESSED");
                    wrefresh(help_window);
                    exit_program = true;
                }
            }
        }
    }


return 5;

//     // // BEGIN deselection workaround. Not totally sure why it works.
//     // if (mouse_event.bstate & BUTTON1_PRESSED)
//     // {
//     //     attron(COLOR_PAIR(6));
//     //     // mvaddstr(0, 20, "BUTTON1_PRESSED");
//     //     mvaddstr(0, 0, "?");
//     //     attroff(COLOR_PAIR(6));
//     //     refresh();
//     //     return;
//     // }
//     // if (mouse_event.bstate & BUTTON1_RELEASED)
//     // {
//     //     attron(COLOR_PAIR(6));
//     //     mvaddstr(0, 0, " ");
//     //     attroff(COLOR_PAIR(6));
//     //
//     //     refresh();
//     //     return;
//     // }
//     // // END deselection workaround.
//     //
//     // if (options_is_selected && mouse_event.bstate & BUTTON2_RELEASED)
//     // {
//     //     std::ofstream f("/tmp/System.halt");
//     //     f.close();
//     //
//     //     exit(0); // Really should send signal to close all threads then exit.
//     //
//     //     return;
//     // }
//     // else if ((GoldLinux_is_selected) && (mouse_event.bstate & BUTTON2_RELEASED))
//     // {
//     //     std::ofstream f("/tmp/GoldLinux.start");
//     //     f.close();
//     //
//     //     GoldLinux_is_selected = false;
//     //     return;
//     // }
//     // else if ((GoldWin10_is_selected) && (mouse_event.bstate & BUTTON2_RELEASED))
//     // {
//     //     std::ofstream f("/tmp/GoldWin10.start");
//     //     f.close();
//     //
//     //     GoldWin10_is_selected = false;
//     //     return;
//     // }
//     // else if ((SilverWin_is_selected) && (mouse_event.bstate & BUTTON2_RELEASED))
//     // {
//     //     std::ofstream f("/tmp/SilverWin.start");
//     //     f.close();
//     //
//     //     SilverWin_is_selected = false;
//     //     return;
//     // }
//     //
//     // if ((mouse_event.bstate & BUTTON3_RELEASED))
//     // {
//     //     if (wenclose(options, mouse_event.y, mouse_event.x) &&
//     //         m_vm_states.GoldLinux_is_running == false &&
//     //         m_vm_states.GoldWin10_is_running == false &&
//     //         m_vm_states.SilverWin_is_running == false)
//     //     {
//     //         wbkgd(options, COLOR_PAIR(15) | A_BOLD );
//     //         mvwaddstr(options, 0, 0, "YES?");
//     //         wrefresh(options);
//     //
//     //         options_is_selected = true;
//     //     }
//     //     else if (wenclose(GoldLinuxWindow, mouse_event.y, mouse_event.x) == true &&
//     //         GoldLinux_is_selected == false &&
//     //         m_vm_states.GoldLinux_is_running == false &&
//     //         m_vm_states.GoldWin10_is_running == false) //NOTE GoldLinux and GoldWin10 can't run at the same time
//     //     {
//     //         box(GoldLinuxWindow, 0 , 0);
//     //         wbkgd(GoldLinuxWindow, COLOR_PAIR(13) | A_BOLD);
//     //
//     //         wrefresh(GoldLinuxWindow);
//     //
//     //         GoldLinux_is_selected = true;
//     //
//     //         std::thread(&Layout::deselectBox, this, "GoldLinux").detach();
//     //     }
//     //     else if (wenclose(GoldWin10Window, mouse_event.y, mouse_event.x) == true &&
//     //              GoldWin10_is_selected == false &&
//     //              m_vm_states.GoldWin10_is_running == false &&
//     //              m_vm_states.GoldLinux_is_running == false) //NOTE GoldLinux and GoldWin10 can't run at the same time
//     //     {
//     //         box(GoldWin10Window, 0 , 0);
//     //         wbkgd(GoldWin10Window, COLOR_PAIR(13) | A_BOLD);
//     //
//     //         wrefresh(GoldWin10Window);
//     //
//     //         GoldWin10_is_selected = true;
//     //
//     //         std::thread(&Layout::deselectBox, this, "GoldWin10").detach();
//     //     }
//     //     else if (wenclose(SilverWinWindow, mouse_event.y, mouse_event.x) == true &&
//     //              SilverWin_is_selected == false &&
//     //              m_vm_states.SilverWin_is_running == false)
//     //     {
//     //         box(SilverWinWindow, 0 , 0);
//     //         wbkgd(SilverWinWindow, COLOR_PAIR(13) | A_BOLD);
//     //
//     //         wrefresh(SilverWinWindow);
//     //
//     //         SilverWin_is_selected = true;
//     //
//     //         std::thread(&Layout::deselectBox, this, "SilverWin").detach();
//     //     }
//     // }
}
