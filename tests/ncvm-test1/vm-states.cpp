#include "vm-states.hpp"
// #include <iostream>
#include <filesystem>

VmStates::VmStates()
{
    // GoldLinux_is_running = true;
    // std::cout << "GoldLinux_is_running: " << GoldLinux_is_running << std::endl;

    if (std::filesystem::exists("/var/run/libvirt/qemu/GoldLinux.pid"))
    {
        GoldLinux_is_running = true;
    }
    if (std::filesystem::exists("/var/run/libvirt/qemu/GoldWin10.pid"))
    {
        GoldWin10_is_running = true;
    }
    if (std::filesystem::exists("/var/run/libvirt/qemu/SilverWin.pid"))
    {
        SilverWin_is_running = true;
    }
}

VmStates::~VmStates()
{
}
