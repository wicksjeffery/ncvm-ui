#include "stdscr.hpp"

#include <iostream>
#include <curses.h>


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


