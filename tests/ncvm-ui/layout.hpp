#ifndef LAYOUT_HPP
#define LAYOUT_HPP
// SilverWin
// SilverLin
// GoldLinux
// GoldWin10
// Empty4Now
// --EMPTY--
#include <panel.h>
#include <thread>

class Layout
{
    // std::thread t1;

    struct PANEL_DATA {
        bool hide = false;	/* TRUE if panel is hidden */
    };

    WINDOW *help_window;
    PANEL *help_panel;
    PANEL_DATA help_panel_data;
    PANEL_DATA *help_panel_data_temp;
    void createHelpWindow(const char* help_text);
    // // VmStates m_vm_states;
    //
    WINDOW* menu_options;
    // WINDOW* machines_window;
    //
    // WINDOW* logger_window;
    // WINDOW* GoldLinuxWindow;
    // WINDOW* GoldWin10Window;
    // WINDOW* SilverWinWindow;
    //
    bool exit_program = false;
    void createToolBar();
    // void create_outter_machines_window();
    // void create_inner_machines_boxes();
    // void create_logger_window();
    //
    // bool options_is_selected;
    // bool GoldLinux_is_selected;
    // bool GoldWin10_is_selected;
    // bool SilverWin_is_selected;
    //
    // void deselectBox(std::string vm_name); //to unselect box
    //
    //
    // void drawVMBox(int horizontal_position,
    //                std::string vm_name,
    //                bool vm_is_running);

    // void handleMouseEvents();
public:
    // Layout(VmStates vm_states);
    Layout();
    ~Layout();

    // void updateVMStatus(VmStates vm_states);

    // WINDOW* getLoggerWindow();

    // void handleMouseEvents(MEVENT mouse_event);
    int handleMouseEvents(int n);
};

#endif
