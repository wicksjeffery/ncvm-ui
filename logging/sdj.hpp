#ifndef LOGGING_SDJ_HPP
#define LOGGING_SDJ_HPP

#include <systemd/sd-journal.h>
#include <string>

namespace Logging
{
    // Systemd Journal
    class SDJ
    {
        int utility_value;

        const char* _priority_level;

    public:
        sd_journal *j;

        SDJ(const char*);
        ~SDJ();
        int listen(bool, std::string);

        bool getNext();

        void setOperationResult(bool r)
        {
            utility_value = r;
        }

        int getOperationResult() const
        {
            return utility_value;
        }

        const char* getPriorityLevel() const
        {
            return _priority_level;
        }

        std::string getData();
    };
}




#endif
