#include "manager.hpp"
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
#include <future>
#include "sdj.hpp"
#include <array>
#include <unordered_map>
#include "writer.hpp"

//ALERT System Logs go to "system log window" and application logs go to "application log window as well as systemd-logger"


Logging::Manager& Logging::Manager::getInstance()
{
    // Local static variable, initialized only once and thread-safe since C++11
    static Manager instance;
    return instance;
}


Logging::Manager::Manager()
{
    //

    // m_sdjs["one"] = SDJ("PRIORITY=0");
/*
    m_sdjs.emplace(1, SDJ("PRIORITY=0"));*/
    write("Initializing...");
}

// #include "ncurses.h"
void Logging::Manager::write(std::string entry)
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

void Logging::Manager::j_open()
{
    // int return_code;
    //
    // return_code = sd_journal_open(&emerg_log, SD_JOURNAL_LOCAL_ONLY);
    // // return_code = sd_journal_open(&test, SD_JOURNAL_LOCAL_ONLY);
    // if (return_code < 0)
    // {
    //     // fprintf(stderr, "Failed to open journal: %s\n", strerror(-return_code)); //TODO: throw instead.
    //     std::stringstream ss;
    //     ss << "Failed to open journal: " << strerror(-return_code) << std::endl;
    //     // continue;
    //     throw(std::runtime_error(ss.str()));
    // }

    for (int i = 0; i < journal_objects.size(); ++i)
    {
        int return_code;

        return_code = sd_journal_open(&journal_objects[i], SD_JOURNAL_LOCAL_ONLY);

        if (return_code < 0)
        {
            // fprintf(stderr, "Failed to open journal: %s\n", strerror(-return_code)); //TODO: throw instead.
            std::stringstream ss;
            ss << "Failed to open journal: " << strerror(-return_code) << std::endl;
            // continue;
            throw(std::runtime_error(ss.str()));
        }

        return_code = sd_journal_seek_tail(journal_objects[i]);

        if (return_code < 0)
        {
            // fprintf(stderr, "Failed to open journal: %s\n", strerror(-return_code)); //TODO: throw instead.
            std::stringstream ss;
            ss << "Journal failed to seek to end: " << strerror(-return_code) << std::endl;
            // continue;
            throw(std::runtime_error(ss.str()));
        }

    }
}

void Logging::Manager::j_match()
{
    // int return_code;
    //
    // // Set the filter for priority 3 (LOG_ERR)
    // return_code = sd_journal_add_match(journal_objects[0], "PRIORITY=4", 0);
    // // sd_journal_add_match(j, priority, 0);
    // // sd_journal_add_match(test, priority, 0);
    // if (return_code < 0) {
    //     // fprintf(stderr, "Failed to add priority filter: %s\n", strerror(-return_code));
    //     sd_journal_close(emerg_log);
    //     // return 1;
    //     std::stringstream ss;
    //     ss << "Failed to add priority filter: " << strerror(-return_code) << std::endl;
    //     // continue;
    //     throw(std::runtime_error(ss.str()));
    // }
/*
    for (auto jo : journal_objects)
    {
        int return_code;

        // Set the filter for priority 3 (LOG_ERR)
        return_code = sd_journal_add_match(jo, "PRIORITY=3", 0);
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
    }*/


    int return_code;

    for (int i = 0; i < journal_objects.size(); ++i)
    {
        switch (i)
        {
            case 0:
                // alert
                return_code = sd_journal_add_match(journal_objects[i], "PRIORITY=1", 0);
                break;
            case 1:
                // crit
                return_code = sd_journal_add_match(journal_objects[i], "PRIORITY=2", 0);
                break;
            case 2:
                // err
                return_code = sd_journal_add_match(journal_objects[i], "PRIORITY=3", 0);
                break;
            case 3:
                // warning
                return_code = sd_journal_add_match(journal_objects[i], "PRIORITY=4", 0);
                break;
        }

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
    }
}

int Logging::Manager::j_next(unsigned short n)
{
    int return_code;

    return_code = sd_journal_next(journal_objects[n]);

    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to iterate to next entry: %s\n", strerror(-return_code));

        // sd_journal_close(j); //WARNING TODO close all in the dtor!!
        // return 1;
        std::stringstream ss;
        ss << "Failed to iterate to next entry: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    return return_code;

}

int Logging::Manager::j_wait(unsigned short n)
{
    int return_code;

    /* Reached the end, let's wait for changes, and try again */
    // r = sd_journal_wait(j, (uint64_t) -1);
    return_code = sd_journal_wait(journal_objects[n], (uint64_t) 100000);
    // return_code = sd_journal_wait(journal_objects[n], (uint64_t) 0);

    // usleep(1)
    // printf(".");
    // fflush(stdout);
    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to wait for changes: %s\n", strerror(-return_code));

        // sd_journal_close(j); //WARNING TODO close all in the dtor!


        std::stringstream ss;
        ss << "Failed to wait for changes: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    // continue;
    return return_code;
}

void Logging::Manager::j_get_data(unsigned short n)
{
    // auto now = std::chrono::time_point_cast<std::chrono::seconds>(
    //     std::chrono::system_clock::now()
    // );
    // auto timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);



    int return_code;
    const void *d;
    size_t l;

    return_code = sd_journal_get_data(journal_objects[0], "MESSAGE", &d, &l);

    if (return_code < 0)
    {
        // fprintf(stderr, "Failed to read message field: %s\n", strerror(-return_code));
        std::stringstream ss;
        ss << "Failed to read message field: " << strerror(-return_code) << std::endl;
        // continue;
        throw(std::runtime_error(ss.str()));
    }

    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

    // std::string foo((const char*)d);
    // timestamp.append((const char*)d);

    // std::stringstream ss;
    // ss << timestamp << " " << (const char*)d << std::endl;
    // printf("%.*s\n", (int) l, (const char*) d);
    wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, (const char*) d);
    d = nullptr;
    d =0;
    // wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, ss.str().c_str());
    // wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, timestamp.c_str());
    update_panels();
    doupdate();
}

int Logging::Manager::run1(int n)
{
    int t = 0;

    j_open();
    j_match();

    while (running)
    {
        // for (int i = 0; i < journal_objects.size(); ++i)
        // {
        t = j_next(0);
            // if (j_next(i) == 0)
           if (t == 0)
            {

                unsigned short r = j_wait(0);

                // while (j_wait(i) == SD_JOURNAL_NOP);
                // // if (j_wait(i) == SD_JOURNAL_NOP) continue;
                // if (r == SD_JOURNAL_NOP) continue;
                if (r == SD_JOURNAL_NOP)
                {
                    // j_get_data(0);
                    continue;
                }
                // // if (r == SD_JOURNAL_INVALIDATE ) j_get_data(i);
                // // if (r != SD_JOURNAL_INVALIDATE) j_get_data(i);

                // continue;

            }
            else if (t == 1)
            {
                j_get_data(0);
            }
            // else
            // {
            //     std::stringstream ss;
            //     ss << "j_next reterned: " << SD_JOURNAL_APPEND << std::endl;
            //     throw(std::runtime_error(ss.str()));;
            // }

            // j_get_data(i);
        // }
    }


    //sd_journal_close(j); //WARNING TODO close all in the dtor!

    return 9;
}

void Logging::Manager::runSDJ1()
{
    // int return_code;
    //
    // while (running)
    // {
    //     return_code = sd_journal_next(sdj1.j);
    //
    //     if (return_code < 0)
    //     {
    //         std::stringstream ss;
    //         ss << "Failed to iterate to next entry: " << strerror(-return_code) << std::endl;
    //         throw(std::runtime_error(ss.str()));
    //     }
    //     else if (return_code == 0)
    //     {
    //         return_code = sd_journal_wait(sdj1.j, (uint64_t) -1);
    //         if (return_code < 0)
    //         {
    //             std::stringstream ss;
    //             ss << "Failed to wait for changes: " << strerror(-return_code) << std::endl;
    //             throw(std::runtime_error(ss.str()));
    //         }
    //         else if (return_code == SD_JOURNAL_NOP)
    //         {
    //             continue;
    //         }
    //         else if (return_code == SD_JOURNAL_APPEND || SD_JOURNAL_INVALIDATE)
    //         {
    //             int return_code;
    //             const void *d;
    //             size_t l;
    //
    //             return_code = sd_journal_get_data(sdj1.j, "MESSAGE", &d, &l);
    //
    //             if (return_code < 0)
    //             {
    //                 // fprintf(stderr, "Failed to read message field: %s\n", strerror(-return_code));
    //                 std::stringstream ss;
    //                 ss << "Failed to read message field: " << strerror(-return_code) << std::endl;
    //                 // continue;
    //                 throw(std::runtime_error(ss.str()));
    //             }
    //
    //             UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    //
    //             wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, (const char*) d);
    //             wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
    //             // update_panels();
    //             // doupdate();
    //         }
    //     }
    //
    // }





        // std::cout << "\a" << std::flush;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
}


void Logging::Manager::runSDJ1OLD2()
{
    // const void *d;
    // size_t l;
    // while (running)
    // {
    //
    //     int return_code = sd_journal_wait(sdj1.j, (uint64_t) -1);
    //     if (return_code < 0)
    //     {
    //         std::stringstream ss;
    //         ss << "Failed to wait for changes: " << strerror(-return_code) << std::endl;
    //         throw(std::runtime_error(ss.str()));
    //     }
    //     else if (return_code == SD_JOURNAL_NOP || return_code == SD_JOURNAL_INVALIDATE)
    //     {
    //         continue;
    //     }
    //     else if (return_code == SD_JOURNAL_APPEND )
    //     {
    //         const void *d;
    //         size_t l;
    //
    //         return_code = sd_journal_get_data(sdj1.j, "MESSAGE", &d, &l);
    //
    //         if (return_code < 0)
    //         {
    //             // fprintf(stderr, "Failed to read message field: %s\n", strerror(-return_code));
    //             std::stringstream ss;
    //             ss << "Failed to read message field: " << strerror(-return_code) << std::endl;
    //             // continue;
    //             throw(std::runtime_error(ss.str()));
    //         }
    //
    //         UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    //
    //         wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, (const char*) d);
    //         wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
    //
    //         // std::cout << "\a" << std::flush;
    //         // std::this_thread::sleep_for(std::chrono::seconds(10));
    //     }
    //
    //
    //
    //
    //
    //     return_code = sd_journal_next(sdj1.j);
    //
    //     if (return_code < 0)
    //     {
    //         std::stringstream ss;
    //         ss << "Failed to iterate to next entry: " << strerror(-return_code) << std::endl;
    //         throw(std::runtime_error(ss.str()));
    //     }
    //     else if (return_code == 0)
    //     {
    //         continue;
    //     }
    //     else if (return_code == 1)
    //     {
    //         return_code = sd_journal_get_data(sdj1.j, "MESSAGE", &d, &l);
    //
    //         if (return_code < 0)
    //         {
    //             // fprintf(stderr, "Failed to read message field: %s\n", strerror(-return_code));
    //             std::stringstream ss;
    //             ss << "Failed to read message field: " << strerror(-return_code) << std::endl;
    //             // continue;
    //             throw(std::runtime_error(ss.str()));
    //         }
    //
    //         UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    //
    //         wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%.*s\n", (int) l, (const char*) d);
    //         wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
    //         // update_panels();
    //         // doupdate();
    //     }
    // }

    // std::cout << "\a" << std::flush;
    // std::this_thread::sleep_for(std::chrono::seconds(2));
}


int Logging::Manager::run(int n = 0)
{
    // SDJ sdj0("PRIORITY=0");
    // SDJ sdj1("PRIORITY=1");
    // SDJ sdj2("PRIORITY=2");
    // SDJ sdj3("PRIORITY=3");
    // SDJ sdj4("PRIORITY=4");

    std::array<SDJ, 5> sdjs =
    {
        SDJ("PRIORITY=0"),
        SDJ("PRIORITY=1"),
        SDJ("PRIORITY=2"),
        SDJ("PRIORITY=3"),
        SDJ("PRIORITY=4")
    };
    std::ofstream outputFile;
    outputFile.open("/tmp/debug3.txt", std::ofstream::out | std::ofstream::app);

    std::string::size_type found_pos;

    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance(); //TODO: don't do this every time'

    while (running)
    {
        // int rx0 = sdj0.getNext();
        // int rx1 = sdj1.getNext();
        // int rx2 = sdj2.getNext();
        // int rx3 = sdj3.getNext();
        // int rx4 = sdj4.getNext();



        // for (auto& sdj : sdjs)
        for (int i = 0; i < sdjs.size(); i++)
        {
            sdjs[i].setOperationResult(sdjs[i].getNext());
        }

        // int new_journal_entries_found = 0;
        // for (auto& sdj : sdjs)
        for (int i = 0; i < sdjs.size(); i++)
        {
            if (sdjs[i].getOperationResult()) goto NEWLOGENTRIESFOUND;
        }

        continue;

        NEWLOGENTRIESFOUND:

        for (int i = sdjs.size() - 1; i >= 0; --i)
        // for (auto sdj : sdjs) // TODO run this backwards
        {

        if (sdjs[i].getOperationResult() == 1)
            // if (sdj.getOperationResult() == 1)
            {


                // outputFile << "hello" << std::endl;
                // outputFile.close();

                // sdj.getData();
                // found_pos = sdjs[i].getData().find("4=", 0);

                Writer formatter(sdjs[i].getData()); //not sure what to name it yet.
                formatter.write();
                // if (sdjs[i].getData().find("4=", 0) != std::string::npos)
                // {
                    // formatter.write(sdjs[i].getData());
                // }


                // if (found_pos == std::string::npos)
                // {
                //     throw(std::runtime_error("Programming error: NO PRIORITIES FOUND."));
                // }
                // if (sdjs[i].getData().find("4=", 0) != std::string::npos)
                // {
                //     // Lowest priority, set least important-looking color.
                //     wattron(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(2) | A_BOLD);
                //     wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%s\n", sdjs[i].getData().c_str());
                //     wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(2) );
                //     wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
                //
                //     // continue;
                // }
                //
                // else if (sdjs[i].getData().find("3=", 0) != std::string::npos)
                // {
                //     wattron(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(7) | A_BOLD);
                //     wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%s\n", sdjs[i].getData().c_str());
                //     wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(7) | A_BOLD);
                //     wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
                // }

                // found_pos = sdjs[i].getData().find("2", 0);
                //
                // if (found_pos == std::string::npos)
                // {
                //     throw(std::runtime_error("Programming error: NO PRIORITIES FOUND."));
                // }
                // else
                // {
                //     // init_pair(7, COLOR_WHITE, COLOR_RED);
                //     wattron(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(3));
                //     wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%s\n", sdjs[i].getData().c_str());
                //     wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(3));
                //     wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
                // }
                //
                // found_pos = sdjs[i].getData().find("1", 0);
                //
                // if (found_pos == std::string::npos)
                // {
                //     throw(std::runtime_error("Programming error: NO PRIORITIES FOUND."));
                // }
                // else
                // {
                //     // init_pair(7, COLOR_WHITE, COLOR_RED);
                //     wattron(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(5));
                //     wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%s\n", sdjs[i].getData().c_str());
                //     wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(5));
                //     wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
                // }
                //
                // found_pos = sdjs[i].getData().find("0", 0);
                //
                // if (found_pos == std::string::npos)
                // {
                //     throw(std::runtime_error("Programming error: NO PRIORITIES FOUND."));
                // }
                // else
                // {
                //     // init_pair(7, COLOR_WHITE, COLOR_RED);
                //     wattron(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(7));
                //     wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%s\n", sdjs[i].getData().c_str());
                //     wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(7));
                //     wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
                // }

                // std::string test = sdjs[i].getData();
                // outputFile << test << std::endl;
                //
                // wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "%s\n", sdjs[i].getData().c_str());
                // // // wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(7));
                // wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
            }
        }

        // // throw(std::runtime_error("All done"));

    }

    return 0;
}



int Logging::Manager::start()
{

    // SDJ sdj1;
    // // std::string j1;
    // //
    // std::thread thread1(&Logging::Manager::runSDJ1, this);
    //
    // thread1.detach();



    return 0;
}


Logging::Manager::~Manager()
{
    write("Stopping...");

    // for (int i = 0; i < journal_objects.size(); ++i)
    // {
    //     sd_journal_close(journal_objects[i]);
    // }
}
