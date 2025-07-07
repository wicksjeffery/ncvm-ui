#ifndef LOGGING_SDJ_HPP
#define LOGGING_SDJ_HPP

#include <systemd/sd-journal.h>
#include <string>

namespace Logging
{
    // Systemd Journal
    class SDJ
    {

    public:
        sd_journal *j;

        SDJ(const char*);
        ~SDJ();
        int listen(bool, std::string);

        bool getNext();

    };
}




#endif
