#include "layout.hpp"
#include "vm-monitor.hpp"
#include "vm-states.hpp"

#include <thread>
#include <filesystem>

// Write log data to logger_window. This can be relocated to inside Layout.
void startLoggerWindow(WINDOW* logger_window)
{
    std::array<char, 128> buffer;

    FILE* pipe = popen("journalctl -f", "r");

    if (!pipe) throw std::runtime_error("popen() failed!");


    while ((fgets(buffer.data(), buffer.size(), pipe) != NULL))
    {
            waddstr(logger_window, buffer.data());
            wrefresh(logger_window);

            sleep(1);
    }
}


int main()
{
    VmStates vm_states;

    if (std::filesystem::exists("/var/run/libvirt/qemu/GoldLinux.pid"))
    {
        vm_states.GoldLinux_is_running = true;
    }
    if (std::filesystem::exists("/var/run/libvirt/qemu/GoldWin10.pid"))
    {
        vm_states.GoldWin10_is_running = true;
    }
    if (std::filesystem::exists("/var/run/libvirt/qemu/SilverWin.pid"))
    {
        vm_states.SilverWin_is_running = true;
    }

    bool stop_vm_monitor = false;
    std::thread monitor_vm_status(watch_vm_dir, &stop_vm_monitor, &vm_states);

    Layout layout(vm_states);


    // sleep(15);
    // stop_vm_monitor = true;
    // monitor_vm_status.join();


    WINDOW* lw = layout.getLoggerWindow();

    std::thread (startLoggerWindow, lw).detach();

    keypad(stdscr, TRUE); // For mouse events.
    mousemask(BUTTON3_RELEASED | BUTTON2_RELEASED | BUTTON1_PRESSED | BUTTON1_RELEASED, NULL);

    while (true)
    {
        // usleep(300);
        layout.updateVMStatus(vm_states); // maybe add a delay in this function

        int getch_return_value = getch();

        if (getch_return_value == KEY_MOUSE)
        {
            MEVENT mouse_event;

            if (getmouse(&mouse_event) == OK)
            {
                layout.handleEvents(mouse_event);
            }
        }
    }


    return 0;
}

