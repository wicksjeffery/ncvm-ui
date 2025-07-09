#include "sdj.hpp"
#include <iostream>
#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>
#include <fstream>

#include <errno.h>
#include <string>
#include "../../command-line-args.hpp"

Logging::SDJ::SDJ(const char* priority_level)
    :
        _priority_level(priority_level)
{
    int return_code;

    return_code = sd_journal_open(&j, SD_JOURNAL_LOCAL_ONLY);

    if (return_code < 0)
    {
        std::stringstream ss;
        ss << "Failed to open journal: " << strerror(-return_code) << std::endl;
        throw(std::runtime_error(ss.str()));
    }

    return_code = sd_journal_add_match(j, priority_level, 0);

    if (return_code < 0)
    {
        std::stringstream ss;
        ss << "Failed to add priority filter: " << strerror(-return_code) << std::endl;
        throw(std::runtime_error(ss.str()));
    }

    CommandLineArgs& cl = CommandLineArgs::getInstance();

    // Allow user to specify how many logs they want to see when the app starts.
    JE number_of_journal_entries = cl.getStartingJournals();

    if (number_of_journal_entries == All)
    {
        return;
    }
    else if (number_of_journal_entries == New)
    {
        //BEGIN only new
        return_code = sd_journal_seek_tail(j);

        if (return_code < 0)
        {
            //TODO: throw using same pattern as in command-line-args.cpp
            std::stringstream ss;
            ss << "Journal failed to seek to end: " << strerror(-return_code) << std::endl;
            // continue;
            throw(std::runtime_error(ss.str()));
        }

        return_code = sd_journal_previous(j); // Move to the last valid entry
        if (return_code < 0) {
            std::stringstream ss;
            ss << "Journal failed to seek to end: " << strerror(-return_code) << std::endl;
            // continue;
            throw(std::runtime_error(ss.str()));
        }
        //END only new
    }
    else if (number_of_journal_entries == Last)
    {
        //BEGIN since last boot
        sd_id128_t boot_id;
        // uint64_t monotonic_timestamp;
        return_code = sd_id128_get_boot(&boot_id);
        if (return_code < 0 )
        {
            std::stringstream ss;
            ss << "Journal failed to get boot id: " << strerror(-return_code) << std::endl;
            throw(std::runtime_error(ss.str()));
        }

        return_code = sd_journal_seek_monotonic_usec(j, boot_id, 0);
        if (return_code < 0 )
        {
            std::stringstream ss;
            ss << "SDJ FAIL: sd_journal_seek_monotonic_usec: " << strerror(-return_code) << std::endl;
            throw(std::runtime_error(ss.str()));
        }
        //END since last boot
    }
}


int Logging::SDJ::listen(bool running, std::string data)
{
    int return_code;

    while (running)
    {
        return_code = sd_journal_next(j);

        if (return_code < 0)
        {
            std::stringstream ss;
            ss << "Failed to iterate to next entry: " << strerror(-return_code) << std::endl;
            throw(std::runtime_error(ss.str()));
        }
        else if (return_code == 0)
        {
            return_code = sd_journal_wait(j, (uint64_t) -1);
            if (return_code < 0)
            {
                std::stringstream ss;
                ss << "Failed to wait for changes: " << strerror(-return_code) << std::endl;
                throw(std::runtime_error(ss.str()));
            }
            else if (return_code == SD_JOURNAL_APPEND)
            {
                continue;
            }

            data = "okay pokay";
        }

        // std::cout << "\a" << std::flush;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 2;
}


void Logging::SDJ::throttleDown()
{
    throttle_speed = 10000;
}



bool Logging::SDJ::getNext()
{
    int r1 = sd_journal_next(j);

    if (r1 < 0)
    {
        std::stringstream ss;
        ss << "Failed to iterate to next entry: " << strerror(-r1) << std::endl;
        throw(std::runtime_error(ss.str()));
    }
    else if (r1 == 0)
    {
        /**
         * @brief SD_JOURNAL_GET_FD(3)
         *
         * int sd_journal_wait(sd_journal *j, uint64_t timeout_usec);
         *
         * If no new journal entries are found, wait timeout_usec. I
         * don't wait indefinately so I can process all four entries.
         */
        // int r2 = sd_journal_wait(j, (uint64_t) 1000000);
        int r2 = sd_journal_wait(j, (uint64_t) throttle_speed);

        if (r2 < 0)
        {
            std::stringstream ss;
            ss << "Failed to wait for changes: " << strerror(-r2) << std::endl;
            throw(std::runtime_error(ss.str()));
        }

        return 0; //no logs
    }

    return 1; //got some logs
}

std::string Logging::SDJ::getData()
{
    // std::ofstream outputFile;

    // outputFile.open("/tmp/debug3.txt", std::ofstream::out | std::ofstream::app);

    const void *d;
    size_t l;
    std::string field("MESSAGE");

    int r3  = sd_journal_get_data(j, field.c_str(), &d, &l);

    if (r3 < 0)
    {
        std::stringstream ss;
        ss << "Failed to read message field: " << strerror(-r3) << std::endl;
        throw(std::runtime_error(ss.str()));
    }

    std::string str((const char*)d);

    // outputFile << (const char*)d << std::endl;
    // outputFile.close();

    std::string::size_type found_pos;
    found_pos = str.find(field, 0);

    if (found_pos != std::string::npos)
    {

        str = str.substr(field.length());

        if (strcmp(_priority_level, "PRIORITY=0") == 0)
        {
            str.insert(0, "Emergency");
        }
        else if (strcmp(_priority_level, "PRIORITY=1") == 0)
        {
            str.insert(0, "Alert");
        }
        else if (strcmp(_priority_level, "PRIORITY=2") == 0)
        {
            str.insert(0, "Critical");
        }
        else if (strcmp(_priority_level, "PRIORITY=3") == 0)
        {
            str.insert(0, "Error");
        }
        else if (strcmp(_priority_level, "PRIORITY=4") == 0)
        {
            str.insert(0, "Warning");
        }
        else throw("Programming error: NO STRINGS MATCH."); //TODO use correct "throw" pattern.
    }
    else
    {
        std::stringstream ss;
        ss << field << " not found: " << std::endl;
        throw(std::runtime_error(ss.str()));
    }

    return str;
}


Logging::SDJ::~SDJ()
{
    sd_journal_close(j);
}
