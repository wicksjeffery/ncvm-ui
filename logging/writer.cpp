#include "writer.hpp"
#include <string>
#include <ncurses.h>

#include "windows/collection.hpp"

Logging::Writer::Writer(std::string log_entry)
    :
        _log_entry(log_entry)
{
    std::string::size_type found_pos;

    found_pos = log_entry.find("Emergency=", 0);

    if (found_pos != std::string::npos)
    {
        color = Emergency;

        return;
    }

    found_pos = log_entry.find("Alert=", 0);

    if (found_pos != std::string::npos)
    {
        color = Alert;

        return;
    }

    found_pos = log_entry.find("Critical=", 0);

    if (found_pos != std::string::npos)
    {
        color = Critical;

        return;
    }

    found_pos = log_entry.find("Error=", 0);

    if (found_pos != std::string::npos)
    {
        color = Error;

        return;
    }

    found_pos = log_entry.find("Warning=", 0);

    if (found_pos != std::string::npos)
    {
        color = Warning;

        return;
    }


    throw(std::runtime_error("writer.cpp Programming error: NO PRIORITIES MATCHED."));
}


void Logging::Writer::write()
{
    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

    wattron(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(color) | A_BOLD);
    wprintw(collection.find("UI::Windows::Journal::Inside")->get_window(), "\n%s", _log_entry.c_str());
    wattroff(collection.find("UI::Windows::Journal::Inside")->get_window(), COLOR_PAIR(color) | A_BOLD);
    wrefresh(collection.find("UI::Windows::Journal::Inside")->get_window());
}
