#include "manager.hpp"
#include "windows/collection.hpp"

#include <ranges>
#include <iostream>
#include <chrono>
#include <format> // For std::format (C++20)
#include <sstream>
#include <iostream>
#include <ncurses.h>
#include <errno.h>
#include <stdio.h>
#include <systemd/sd-journal.h>
#include <future>
#include "sdj.hpp"
#include <array>
#include <unordered_map>
#include "writer.hpp"
#include <syslog.h>

//ALERT System Logs go to "system log window" and application logs go to "application log window as well as systemd-logger"
// std::ofstream outputFile;
// outputFile.open("/tmp/debug3.txt", std::ofstream::out | std::ofstream::app);
// outputFile << "hello" << std::endl;
// outputFile.close();

//TODO: Think about how many times the string is copied from sd_journal_get_data().


Logging::Manager& Logging::Manager::getInstance()
{
    static Manager instance;
    return instance;
}


Logging::Manager::Manager()
{
    //TODO:
    // write("Initializing...");
}

void Logging::Manager::write(unsigned short level, const char* entry)
{
//     // auto now = std::chrono::time_point_cast<std::chrono::seconds>(
//     //     std::chrono::system_clock::now()
//     // );
//     // auto timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);
//     //
//     // std::ofstream ofs;
//     // ofs.open("ncvm.log", std::ofstream::app);
//     // ofs << timestamp << "\t" << entry << std::endl;
//     //
//     //
    //TODO possible to change colors according to log level severity here.
    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    wprintw(collection.find("UI::Windows::ApplicationStatus::Box")->get_window(), "%s", entry);
    wrefresh(collection.find("UI::Windows::ApplicationStatus::Box")->get_window());
//     //
//     // ofs.close();
//
//
//
    openlog("ncvm-ui", LOG_PID, LOG_DAEMON); // Open log with program name, PID, and daemon facility
    // syslog(LOG_NOTICE, "This is a notice message sent via syslog.");
    syslog(level, "%s", entry);
    //TODO use syslog log levels instead of my own enum.
    // syslog(LOG_WARNING, entry.c_str());
    closelog();
}



int Logging::Manager::display_tail(int n = 0)
{
    //TODO consider setting priority levels from cmdline options.
    std::array<SDJ, 5> sdjs =
    {
        SDJ("PRIORITY=0"),
        SDJ("PRIORITY=1"),
        SDJ("PRIORITY=2"),
        SDJ("PRIORITY=3"),
        SDJ("PRIORITY=4")
    };


    while (running)
    {
        /**
         * @brief Wrap SD_JOURNAL_NEXT(3)
         *
         * Go to the next journal entry and wait for a new entry. Store the result
         * of each.
         */
        for (auto& sdj : sdjs)
        {
            sdj.setOperationResult(sdj.getNext());
        }

        /**
         * @brief If 1, then there's a new entry.
         *
         * If any SDJ object returned 1 from getNext(), then there's a
         * new entry. Otherwise, go back to the top of the loop.
         */
        for (auto& sdj : sdjs)
        {
            if (sdj.getOperationResult()) goto NEWLOGENTRIESFOUND;
        }

        /**
         * @brief Logging output throttle speed
         *
         * This is a little feature to improve the feel of the app. Meaning:
         * The wait time is slow enough so the mouse feels reactive but fast
         * enough that it can get through the log entries quickly.
         *
         * However, after there has been three cycles of no logs flowing,
         * throttle it down to save on cycles.
         */
        if (sdj_throttle != 3)
        {
            sdj_throttle++;

            if (sdj_throttle == 3)
            {
                for (auto& sdj : sdjs)
                {
                    sdj.throttleDown();
                }
            }
        }

        continue;

        NEWLOGENTRIESFOUND:


        /**
         * @brief C++20 range in reverse
         *
         * Print entries starting with least severe.
         */
        for (auto& sdj : std::views::reverse(sdjs))
        {

            if (sdj.getOperationResult() == 1)
            {
                Writer formatter(sdj.getData()); //not sure what to name it yet.
                formatter.write();
            }
        }
    }

    return 0;
}


Logging::Manager::~Manager()
{
    //TODO:
    // write("Stopping...");
}
