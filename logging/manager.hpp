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
        // Private constructor to prevent direct instantiation
        Manager();
        ~Manager();
        // Delete copy constructor and assignment operator to prevent copying
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;


        void j_open();
        void j_match();
        int j_next(unsigned short);
        int j_wait(unsigned short);
        void j_get_data(unsigned short);


        std::array<sd_journal* , 1> journal_objects;

        // SDJ sdj1;

        void runSDJ1();
        void runSDJ1OLD2();

        // std::unordered_map<SDJ(const char*), unsigned short> m_sdjs;
        // std::unordered_map<unsigned short, SDJ(const char*)> m_sdjs;

    public:
        // Static method to get the single instance of Manager
        static Manager& getInstance();

        void write(std::string);

        int run1(int);
        int run(int);
        int start();

        void quit() { running = false; }

        bool running = true;


    };
}
#endif

