#ifndef LOGGING_MANAGER_HPP
#define LOGGING_MANAGER_HPP


#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>
#include <systemd/sd-journal.h>
#include <array>
#include "sdj.hpp"
#include <unordered_map>
namespace Logging
{
    class Manager
    {
        Manager();
        ~Manager();
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;

        bool running = true;
        unsigned short sdj_throttle = 0;

    public:
        static Manager& getInstance();

        void write(unsigned short, const char*);

        int display_tail(int);

        void quit() { running = false; }
    };
}
#endif

