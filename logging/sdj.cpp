#include "sdj.hpp"
#include <iostream>
#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>

#include <errno.h>

Logging::SDJ::SDJ(const char* priority_level)
{
    int return_code;

    return_code = sd_journal_open(&j, SD_JOURNAL_LOCAL_ONLY);

    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to open journal: %s\n", strerror(-return_code)); //TODO: throw instead.
        std::stringstream ss;
        ss << "Failed to open journal: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    return_code = sd_journal_add_match(j, priority_level, 0);

    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to add priority filter: %s\n", strerror(-return_code));
        // sd_journal_close(journal_objects[i]);
        // return 1;
        std::stringstream ss;
        ss << "Failed to add priority filter: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    // return_code = sd_journal_seek_tail(j);
    //
    // if (return_code < 0)
    // {
    //     // fprintf(stderr, "Failed to open journal: %s\n", strerror(-return_code)); //TODO: throw instead.
    //     std::stringstream ss;
    //     ss << "Journal failed to seek to end: " << strerror(-return_code) << std::endl;
    //     // continue;
    //     throw(std::runtime_error(ss.str()));
    // }
    //
    // return_code = sd_journal_previous(j); // Move to the last valid entry
    // if (return_code < 0) {
    //     std::stringstream ss;
    //     ss << "Journal failed to seek to end: " << strerror(-return_code) << std::endl;
    //     // continue;
    //     throw(std::runtime_error(ss.str()));
    // }

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
        int r2 = sd_journal_wait(j, (uint64_t) 10000);

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




Logging::SDJ::~SDJ()
{
    sd_journal_close(j);
}
