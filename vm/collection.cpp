#include "collection.hpp"
// #include "../logger.hpp"

#include <fstream>

VM::Collection& VM::Collection::getInstance()
{
    // Local static variable, initialized only once and thread-safe since C++11
    static Collection instance;
    return instance;
}

// void VM::Collection::printAll()
// {
//     std::ofstream outputFile;
//     outputFile.open("/tmp/freebug.txt");
//     outputFile << "blahblah" << std::endl;
//     outputFile.close();
//
//
//     // Logger& logger = Logger::getInstance();
//
//     // for (auto const& [key, val] : m_vms)
//     // {
//
//         // std::cout << "\a";
//         // logger.write("key123");
//     // }
// }



// VM::Collection::~Collection()
// {}
