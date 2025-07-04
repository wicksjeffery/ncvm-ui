#include "logger.hpp"
#include "windows/collection.hpp"

#include <iostream>
#include <chrono>
#include <format> // For std::format (C++20)
#include <sstream>
#include <iostream>
#include <ncurses.h>
#include <errno.h>
#include <stdio.h>
#include <systemd/sd-journal.h>

//ALERT System Logs go to "system log window" and application logs go to "application log window as well as systemd-logger"


Logger& Logger::getInstance()
{
    // Local static variable, initialized only once and thread-safe since C++11
    static Logger instance;
    return instance;
}


Logger::Logger()
{
    write("Initializing...");
}

// #include "ncurses.h"
void Logger::write(std::string entry)
{
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(
        std::chrono::system_clock::now()
    );
    auto timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);

    std::ofstream ofs;
    ofs.open("ncvm.log", std::ofstream::app);
    ofs << timestamp << "\t" << entry << std::endl;


    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

    wprintw(collection.find("UI::Windows::Status::Inside")->get_window(), "\n%s", entry.c_str());
    // wrefresh(collection.find("Inside")->get_window());

    ofs.close();
}

void Logger::j_open()
{
    int return_code;

    return_code = sd_journal_open(&emerg_log, SD_JOURNAL_LOCAL_ONLY);
    // return_code = sd_journal_open(&test, SD_JOURNAL_LOCAL_ONLY);
    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to open journal: %s\n", strerror(-return_code)); //TODO: throw instead.
        std::stringstream ss;
        ss << "Failed to open journal: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }
}

void Logger::j_match()
{
    int return_code;

    // Set the filter for priority 3 (LOG_ERR)
    return_code = sd_journal_add_match(emerg_log, "PRIORITY=3", 0);
    // sd_journal_add_match(j, priority, 0);
    // sd_journal_add_match(test, priority, 0);
    if (return_code < 0) {
        // fprintf(stderr, "Failed to add priority filter: %s\n", strerror(-return_code));
        sd_journal_close(emerg_log);
        // return 1;
        std::stringstream ss;
        ss << "Failed to add priority filter: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }
}

int Logger::j_next()
{
    int return_code;

    return_code = sd_journal_next(emerg_log);

    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to iterate to next entry: %s\n", strerror(-return_code));

        sd_journal_close(emerg_log);
        // return 1;
        std::stringstream ss;
        ss << "Failed to iterate to next entry: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    return return_code;
}

int Logger::j_wait()
{
    int return_code;

    /* Reached the end, let's wait for changes, and try again */
    // r = sd_journal_wait(j, (uint64_t) -1);
    return_code = sd_journal_wait(emerg_log, (uint64_t) 100000);

    // usleep(1)
    // printf(".");
    // fflush(stdout);
    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to wait for changes: %s\n", strerror(-return_code));

        sd_journal_close(emerg_log);


        std::stringstream ss;
        ss << "Failed to wait for changes: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    // continue;
    return return_code;
}

void Logger::j_get_data()
{
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(
        std::chrono::system_clock::now()
    );
    auto timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);

    int return_code;
    const void *d;
    size_t l;

    return_code = sd_journal_get_data(emerg_log, "MESSAGE", &d, &l);

    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to read message field: %s\n", strerror(-return_code));
        std::stringstream ss;
        ss << "Failed to read message field: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

    // printf("%.*s\n", (int) l, (const char*) d);
    wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, (const char*) d);
    update_panels();
    doupdate();
}

int Logger::run(int n)
{

    j_open();
    j_match();
    while (running)
    {
        if (j_next() == 0)
        {
            // int w = j_wait();

            if (j_wait() == SD_JOURNAL_NOP) continue;
        }

        j_get_data();
    }

    sd_journal_close(emerg_log);

    return 9;
}


Logger::~Logger()
{
    // write("Stopping...");
}
