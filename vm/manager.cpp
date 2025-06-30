#include "manager.hpp"

#include <fstream>
#include <filesystem>


VM::Manager::Manager()
{

}

void VM::Manager::validateSavedConfig()
{
    if (!std::filesystem::exists("ncvm-ui.conf"))
    {

    }

    // std::ofstream outputFile("/tmp/debug.txt");
}
