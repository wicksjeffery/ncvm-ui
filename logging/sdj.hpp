#ifndef LOGGING_SDJ_HPP
#define LOGGING_SDJ_HPP

#include <systemd/sd-journal.h>
#include <string>
#include <fstream>
namespace Logging
{
    // Systemd Journal
    class SDJ
    {
        int utility_value;

        const char* _priority_level;

        unsigned int throttle_speed = 100;

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
            // std::ofstream outputFile;

            // outputFile.open("/tmp/debug3.txt", std::ofstream::out | std::ofstream::app);

            // outputFile << _priority_level << " " << utility_value << std::endl;
            return utility_value;
        }

        const char* getPriorityLevel() const
        {
            return _priority_level;
        }

        std::string getData();

        void throttleDown();
    };
}




#endif
