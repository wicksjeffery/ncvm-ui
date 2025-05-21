#ifndef LAYOUT_HPP
#define LAYOUT_HPP
// SilverWin
// SilverLin
// GoldLinux
// GoldWin10
// Empty4Now
// --EMPTY--


#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <memory>
#include <array>
#include "vm-states.hpp"

#include <string>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <chrono>

class Layout
{
    VmStates m_vm_states;

    WINDOW* options;
    WINDOW* machines_window;

    WINDOW* logger_window;
    WINDOW* GoldLinuxWindow;
    WINDOW* GoldWin10Window;
    WINDOW* SilverWinWindow;

    void createToolBar();
    void create_outter_machines_window();
    void create_inner_machines_boxes();
    void create_logger_window();

    bool options_is_selected;
    bool GoldLinux_is_selected;
    bool GoldWin10_is_selected;
    bool SilverWin_is_selected;

    void deselectBox(std::string vm_name); //to unselect box


    void drawVMBox(int horizontal_position,
                   std::string vm_name,
                   bool vm_is_running);

public:
    Layout(VmStates vm_states);
    ~Layout();

    void updateVMStatus(VmStates vm_states);

    WINDOW* getLoggerWindow();

    void handleEvents(MEVENT mouse_event);
};

#endif
