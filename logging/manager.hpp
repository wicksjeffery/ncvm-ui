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


        sd_journal *emerg_log, *alert_log, *crit_log, *err_log;

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


        // void insert(const std::string& key, std::string state)
        // {
        //     m_vms.insert({key, state});
        // }

        // std::string find(const std::string& key) const
        // {
        //     auto search = m_vms.find(key);
        //
        //     return (search != m_vms.end()) ? search->second : throw std::runtime_error("Manager: Key not found.");;
        // }

        // void printAll() const
        // {
        //     std::ofstream outputFile;
        //
        //     // outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);
        //     // outputFile.open("/tmp/debug2.txt");
        //
        //     for (auto const& [key, val] : m_vms)
        //     {
        //         outputFile << "key: " << key << std::endl;
        //     }
        //
        //     outputFile.close();
        // }
    };
}
#endif

