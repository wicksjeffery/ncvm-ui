#ifndef UI_WINDOWS_PRIMARY_STDSCR
#define UI_WINDOWS_PRIMARY_STDSCR

// #include "rectangle.hpp"

#include <ncurses.h>
namespace UI::Windows::Primary
{
    class Stdscr
    {
        short vm1_start_x = 0;
        short vm2_start_x = 0;
        short vm3_start_x = 0;
        short vm4_start_x = 0;

        const unsigned vm_box_width = 17;
        void drawOutterBox(short, short);
        void allocateVMwindows();
        void drawVMwindow(short);
        void writeVMinformation(short, const char*);
    public:
        Stdscr();

        void selectVMwindow(int x_position)
        {
            if (x_position > vm1_start_x && x_position < vm1_start_x + vm_box_width)
            {
                attron(COLOR_PAIR(13));
                mvhline(4, vm1_start_x+1, ' ', vm_box_width-2); //Clear the line.
                mvhline(5, vm1_start_x+1, ' ', vm_box_width-2); //Clear the line.
                mvhline(6, vm1_start_x+1, ' ', vm_box_width-2); //Clear the line.

                // mvprintw(5, column_position, "%s", vm_name.c_str());
                attroff(COLOR_PAIR(13));

                refresh();
            }
        }

        short getVMwindowStartX(short n)
        {
            switch (n)
            {
                case 0: return vm1_start_x;
                case 1: return vm2_start_x;
                case 2: return vm3_start_x;
                case 3: return vm4_start_x;
                default: throw("crap");
            }
        }
    };
}



#endif
