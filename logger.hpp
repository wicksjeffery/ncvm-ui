#ifndef LOGGER_HPP
#define LOGGER_HPP


#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>
#include <systemd/sd-journal.h>

class Logger
{
    // Private constructor to prevent direct instantiation
    Logger();
    ~Logger();
    // Delete copy constructor and assignment operator to prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;


    sd_journal *emerg_log, *alert_log, *crit_log, *err_log;

    void j_open();
    void j_match();
    int j_next();
    int j_wait();
    void j_get_data();

    bool running = true;


public:
    // Static method to get the single instance of Logger
    static Logger& getInstance();

    void write(std::string);

    int run(int);

    void quit() { running = false; }

    // void insert(const std::string& key, std::string state)
    // {
    //     m_vms.insert({key, state});
    // }

    // std::string find(const std::string& key) const
    // {
    //     auto search = m_vms.find(key);
    //
    //     return (search != m_vms.end()) ? search->second : throw std::runtime_error("Logger: Key not found.");;
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

#endif
