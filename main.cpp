// TODO: Do I need to check for memory leak after ctrl-c?

// #include "logger.hpp"
#include "ui/layout.hpp"
#include "ui/event-handler.hpp"
#include "vm/manager.hpp"
#include "logging/manager.hpp"
#include <future>
#include <fstream>
#include <thread>

int main(/*int argc, char **argv*/)
{
    try
    {
        UI::Layout layout;
        // VM::Manager manager;
        Logging::Manager& log_mgr = Logging::Manager::getInstance();

        std::thread logger_thread(&Logging::Manager::run, &log_mgr, 9);

        UI::EventHandler event_handler;


        auto f1 = std::async(&UI::EventHandler::listen, &event_handler, 9);


        // std::ofstream f("/tmp/foo", std::fstream::trunc);

        // f << "okpeT: " << std::hex << std::this_thread::get_id() << std::endl;
        // f.close();
        // std::cout << "\a";

        if (f1.get() == 0)
        {
            //This will be when exit was called from EventHandler. Then close logger.
            log_mgr.quit();
            logger_thread.join();

            return 0;
        } else return 1;

    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;

        return -1;
    }


    return 0;
}
