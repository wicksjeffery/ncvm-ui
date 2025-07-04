#include "manager.hpp"
#include "windows/collection.hpp"

#include <fstream>
#include <filesystem>
#include <array>

VM::Manager::Manager()
{
    // std::array<char, 128> buffer;
    //
    // // FILE* pipe = popen("journalctl -f", "r");
    // FILE* pipe = popen("journalctl -n 20 --no-pager -f", "r");
    //
    // if (!pipe) throw std::runtime_error("popen() failed!");
    //
    //
    // UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
    //
    // waddstr(collection.find("Inside")->get_window(), buffer.data());
    // wrefresh(collection.find("Inside")->get_window());
    // pclose(pipe);

    // waddstr(collection.find("Inside")->get_window(), "abc\ndef\nghi\njkl\nmno");
    // wrefresh(collection.find("Inside")->get_window());
    // waddstr(collection.find("Inside")->get_window(), "qrf\ndeg\npul\nfrq");
    // wrefresh(collection.find("Inside")->get_window());
}

// void VM::Manager::validateSavedConfig()
// {
//     if (!std::filesystem::exists("ncvm-ui.conf"))
//     {
//
//     }
//
//     // std::ofstream outputFile("/tmp/debug.txt");
// }
