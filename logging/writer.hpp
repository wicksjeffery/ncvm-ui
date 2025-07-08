#ifndef LOGGING_WRITER_HPP
#define LOGGING_WRITER_HPP

#include <systemd/sd-journal.h>
#include <string>
#include <fstream>
#include <ncurses.h>

/* journalctl(1)
Level   Severity        Description

0       Emergency       System is unusable
1       Alert           Action must be taken immediately
2       Critical        Critical conditions
3       Error           Errors that need attention
4       Warning         Potential issues
5       Notice          Normal but significant events
6       Informational   General operational messages
7       Debug           Debugging messages for developers
*/


namespace Logging
{
    class Writer
    {
        std::string _log_entry;

        enum COLORS
        {
            Emergency = 7,
            Alert = 8,
            Critical = 9,
            Error = 10,
            Warning = 2
        } color;

    public:
        Writer(std::string);
        void write();

    };
}


#endif
