#include "stdscr.hpp"

#include <iostream>
#include <curses.h>

#include <sstream>


UI::Windows::Primary::Stdscr& UI::Windows::Primary::Stdscr::getInstance()
{
    static Stdscr instance;
    return instance;
}


void UI::Windows::Primary::Stdscr::writeVMinformation(short vm_x_start, const char* label)
{
    attron(COLOR_PAIR(4));
    mvhline(4, vm_x_start+1, ' ', vm_box_width-2);
    mvhline(5, vm_x_start+1, ' ', vm_box_width-2);
    mvhline(6, vm_x_start+1, ' ', vm_box_width-2);
    attroff(COLOR_PAIR(4));


    // attron(COLOR_PAIR(3));
    // //TODO do truncate here
    // mvprintw(5, vm_x_start+2, "%s", label);
    // mvhline(4 + 3 + 1, vm_x_start+1, ' ', vm_box_width-2);
    // attroff(COLOR_PAIR(3));
}

//TODO call this from void VM::Manager::setInitialVMwindowsState() and
//    ->  void VM::Manager::updateVMwindowState(VMState v = VMState())
// or wherever it was that is doing it.
void UI::Windows::Primary::Stdscr::setVMBoxColor(unsigned short vm_number)
{
    const int max_x = 17; //Current allocated width. Maybe put this in a header somwhere

    //TODO maybe move color_to_use setting up here?
    attron(COLOR_PAIR(3));
    mvhline(4, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.
    mvhline(5, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.
    mvhline(6, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.

    //TODO maybe make vm1_start_x in a std::array too, so I can address it with brackets.
    mvprintw(5, vm1_start_x, "%s", vm_names[vm_number].c_str());
    attroff(COLOR_PAIR(3));
}


void UI::Windows::Primary::Stdscr::drawVMwindow(short vm_x_start)
{
    attron(COLOR_PAIR(3));
    mvaddch(3, vm_x_start, ACS_ULCORNER);
    mvvline(4, vm_x_start, ACS_VLINE, 5);
    mvaddch(4 + 3, vm_x_start, ACS_LTEE);
    mvaddch(4 + 3 + 2, (vm_box_width + vm_x_start) - 1, ACS_LRCORNER);

    mvhline(3, vm_x_start + 1, ACS_HLINE, vm_box_width - 2);
    mvhline(4 + 3 + 2, vm_x_start + 1, ACS_HLINE, vm_box_width - 2);

    mvaddch(3, (vm_box_width + vm_x_start) - 1, ACS_URCORNER);
    mvvline(4, (vm_box_width + vm_x_start) - 1, ACS_VLINE, 5);
    mvaddch(4 + 3, (vm_box_width + vm_x_start) - 1, ACS_RTEE);
    mvaddch(4 + 3 + 2, vm_x_start, ACS_LLCORNER);

    mvhline(4 + 3, vm_x_start + 1, ACS_HLINE, vm_box_width - 2);
    attroff(COLOR_PAIR(3));
}


void UI::Windows::Primary::Stdscr::allocateVMwindows()
{
     // Rectangle(7, 17, 3, begin_x)

    const unsigned vm_box_width = 17;//constant
    // BEGIN: setup for vm windows
    // std::ofstream outputFile("/tmp/debug.txt");
    // outputFile << "Space needed: " << 17 * 4 << std::endl;
    short available_space = (COLS-5) - 4;
    // short available_space = (100-5) - 4;
    // outputFile << "Available space is: " << available_space << std::endl;
    short min_space_needed = vm_box_width * 4;
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



    // Distrubute leftover spaces
    switch (leftovers_from_distributed)
    {
        case 1:
            // Put it in the middle.
            vm3_start_x = 1;
            break;
        case 2:
            // Put them on the ends.
            vm1_start_x = 1;
            // fourth is granted.
            break;
        case 3:
            // Put them in the middle and ends
            vm1_start_x = 1;
            vm3_start_x = 1;
            break;
        case 4:
            // Put on all except middle.
            vm1_start_x = 1;
            vm2_start_x = 1;
            vm4_start_x = 1;
            break;
    }

    // const unsigned vm_box_width = 17;//constant
    vm1_start_x += 4 + available_spaces_leftover;
    vm2_start_x += (vm_box_width + vm1_start_x + available_spaces_leftover);
    vm3_start_x += (vm_box_width + vm2_start_x + available_spaces_leftover);
    vm4_start_x += (vm_box_width + vm3_start_x + available_spaces_leftover);
    // END: setup for vm windows
    // first_vm_start_x += 4 + available_spaces_leftover;
    // second_vm_start_x += (vm_box_width + first_vm_start_x + available_spaces_leftover);
    // third_vm_start_x += (vm_box_width + second_vm_start_x + available_spaces_leftover);
    // fourth_vm_start_x += (vm_box_width + third_vm_start_x + available_spaces_leftover);
    // END: setup for vm windows

    // attron(COLOR_PAIR(8));
    //
    // mvprintw(1, 0, "%s%d", "helloer: ", vm1_start_x);
    // refresh();
    // attroff(COLOR_PAIR(8));

    // // BEGIN: Weewee box
    // attron(COLOR_PAIR(3));
    // // move(3, vm1_start_x);
    // mvaddch(3, vm1_start_x, ACS_ULCORNER); // Top-Left corner
    // // addch(ACS_ULCORNER); // Top-Left corner
    // mvhline(3, vm1_start_x + 1, ACS_HLINE, vm_box_width - 2); // Top horizontal
    // // hline(ACS_HLINE, vm_box_width-2); // Top horizontal
    // mvaddch(3, (vm_box_width + vm1_start_x) - 1, ACS_URCORNER); // Top-right corner
    // // addch(ACS_URCORNER); // Top-right corner
    // mvvline(4, (vm_box_width + vm1_start_x) - 1, ACS_VLINE, 5); // Right vertical
    //
    // mvhline(4 + 3, vm1_start_x + 1, ACS_HLINE, vm_box_width - 2);
    //
    // mvvline(4, vm1_start_x, ACS_VLINE, 5);
    //
    // mvaddch(4 + 3, (vm_box_width + vm1_start_x) - 1, ACS_RTEE);
    // mvaddch(4 + 3, vm1_start_x, ACS_LTEE); // Lower-Left corner ACS_LLCORNER
    //
    // mvaddch(4 + 3 + 2, vm1_start_x, ACS_LLCORNER);
    // mvhline(4 + 3 + 2, vm1_start_x + 1, ACS_HLINE, vm_box_width - 2);
    // mvaddch(4 + 3 + 2, (vm_box_width + vm1_start_x) - 1, ACS_LRCORNER);
    // attroff(COLOR_PAIR(3));
    // // END: Weewee box
    //
    // attron(COLOR_PAIR(4));
    // mvhline(4, vm1_start_x+1, ' ', vm_box_width-2);
    // mvhline(5, vm1_start_x+1, ' ', vm_box_width-2);
    // mvhline(6, vm1_start_x+1, ' ', vm_box_width-2);
    // attroff(COLOR_PAIR(4));
    //
    //
    //
    // attron(COLOR_PAIR(3));
    // mvprintw(5, vm1_start_x+2, "%s", "ABCDEFGHIJKLM");
    // mvhline(4 + 3 + 1, vm1_start_x+1, ' ', vm_box_width-2);
    // attroff(COLOR_PAIR(3));

}

void UI::Windows::Primary::Stdscr::drawOutterBox(short start_y, short end_y)
{
    // BEGIN: Inside box
    attron(COLOR_PAIR(2) | A_BOLD);
    mvaddch(start_y, 2, ACS_ULCORNER);
    mvvline(start_y + 1, 2, ACS_VLINE, end_y - (start_y + 1));
    // mvprintw(3, 3, "%d", height);
    mvaddch(end_y, 2, ACS_LLCORNER);

    mvhline(start_y, 3, ACS_HLINE, COLS-7); // Top horizontal
    mvhline(end_y, 3, ACS_HLINE, COLS-7);

    mvaddch(start_y, COLS-4, ACS_URCORNER); // Top-right corner
    mvvline(start_y + 1, COLS-4, ACS_VLINE, end_y - (start_y + 1)); // Right vertical
    mvaddch(end_y, COLS-4, ACS_LRCORNER); // Lower-right corner
    attroff(COLOR_PAIR(2) | A_BOLD);
    // END: Inside box


    // BEGIN: give the box a "shadow"
    attron(COLOR_PAIR(4));
    mvhline(end_y + 1, 3, ' ', COLS-5);
    mvvline(start_y + 1, COLS-3, ' ', end_y - start_y);
    attroff(COLOR_PAIR(4));
    // END: give the box a "shadow"
}



UI::Windows::Primary::Stdscr::Stdscr()
{
    wbkgd(stdscr, COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    mvhline(0, 0, ' ', COLS);

    mvprintw(0, 1, "%s", "Options");

    //BEGIN fill in white spaces behind vm windows
    mvhline(3, 3, ' ', COLS-5);
    mvhline(4, 3, ' ', COLS-5);
    mvhline(5, 3, ' ', COLS-5);
    mvhline(6, 3, ' ', COLS-5);
    mvhline(7, 3, ' ', COLS-5);
    mvhline(8, 3, ' ', COLS-5);
    mvhline(9, 3, ' ', COLS-5);

    mvvline(13, 3, ' ', LINES - 17);
    mvvline(13, 4, ' ', LINES - 17);
    mvvline(13, COLS-5, ' ', LINES - 17);
    mvvline(13, COLS-6, ' ', LINES - 17);
    //END fill in white spaces behind vm windows

    attroff(COLOR_PAIR(3));


    drawOutterBox(2, 10);
    drawOutterBox(13, (LINES-4));

    allocateVMwindows();
    drawVMwindow(vm1_start_x);
    drawVMwindow(vm2_start_x);
    drawVMwindow(vm3_start_x);
    drawVMwindow(vm4_start_x);

    writeVMinformation(vm1_start_x, "             ");
    writeVMinformation(vm2_start_x, "             ");
    writeVMinformation(vm3_start_x, "             ");
    writeVMinformation(vm4_start_x, "             ");

    attron(COLOR_PAIR(12));
    mvhline(LINES-1, 0, ' ', COLS);
    attroff(COLOR_PAIR(12));

    // refresh();
}

#include <fstream>

// void VM::Manager::writeToUI(std::string vm_name, std::string vm_state, unsigned short vm_number)
// TO USE IN event_handler and two other places
void UI::Windows::Primary::Stdscr::writeToUI(std::string vm_name,
                                             // unsigned short state,
                                             std::string state,
                                             unsigned short reason,
                                             unsigned short vm_number,
                                             bool set_initial_state)
{
    const int max_x = 17; //Current allocated width. Maybe put this in a header somwhere
    const unsigned short max_label_len = 13; // This should be in a header too? This is max_x - 4 (13 in this case)

    if (vm_name.length() > max_label_len)
    {
        vm_name.resize(12);
        vm_name.append("~"); //TODO test this with a long vm name
    }

    unsigned short column_position = ((max_x - vm_name.length()) / 2 ) + getVMwindowStartX(vm_number);
    // attron(COLOR_PAIR(8));
    //
    // mvprintw(1, 0, "%s%d", "hewah: ", vm1_start_x);
    // refresh();
    // attroff(COLOR_PAIR(8));

    //todo DO i even need to set colors (earlier)?
    int color_to_use = COLOR_PAIR(8);

    if (!set_initial_state)
    {
        if (state == "shutdown") //6
        {
            color_to_use = COLOR_PAIR(5) | A_BOLD;
        }
        else if (state == "started") //2
        {
             color_to_use = COLOR_PAIR(14) | A_BOLD;
        }
        else if (state == "stopped") //5 Should this be the same color as shutdown?
        {
            color_to_use = COLOR_PAIR(5) | A_BOLD;
        }
        else
        {
            color_to_use = COLOR_PAIR(8) | A_BOLD;
        }
    }
    else if (set_initial_state == true)
    {
        if (state == "shutoff") //5
        {
            color_to_use = COLOR_PAIR(5) | A_BOLD;
        }
        else if (state == "running") //1
        {
            color_to_use = COLOR_PAIR(14) | A_BOLD;
        }
        else
        {
            color_to_use = COLOR_PAIR(8) | A_BOLD;
        }
    }


    attron(color_to_use);
    mvhline(4, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.
    mvhline(5, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.
    mvhline(6, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.

    mvprintw(5, column_position, "%s", vm_name.c_str());
    attroff(color_to_use);

    std::stringstream ss;
    ss << " " <<  state << ": " << reason;


    // INFO: in the unknown even that the string is longer than the
    // available space, truncate it so it doesn't write out of the
    // window.
    std::string tmp = ss.str();
    if (tmp.length() > max_label_len+1)
    {
        tmp.resize(max_label_len);
        tmp.append("~");
    }

    // // Logging::Manager& log_mgr = Logging::Manager::getInstance();
    // // log_mgr.write(LOG_CRIT, tmp.c_str());

    attron(COLOR_PAIR(3) | A_BOLD);
    mvhline(8, getVMwindowStartX(vm_number)+1, ' ', max_x-2); //Clear the line.
    move(8, getVMwindowStartX(vm_number)+1);
    addch(ACS_RARROW);
    printw("%s", tmp.c_str());
    attroff(COLOR_PAIR(3) | A_BOLD);


    refresh();

    // std::ofstream file("blah.txt", std::ofstream::app);
    //
    // file << state << std::endl;
    //
    // file.close();
}



