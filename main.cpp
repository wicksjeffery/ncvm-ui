// TODO: Do I need to check for memory leak after ctrl-c?
// TODO: consider using std::logic_error
// NOTE: users need permissions to work with libvirt: sudo usermod -a -G libvirt <username>

#include "ui/layout.hpp"
#include "ui/event-handler.hpp"
#include "vm/manager.hpp"
#include "logging/manager.hpp"
#include "command-line-args.hpp"
#include <future>
#include <fstream>
#include <thread>

int main(int argc, char* argv[])
{
    try
    {
        CommandLineArgs& cl = CommandLineArgs::getInstance();
        cl.processArgs(argc, argv);

        VM::Manager vmm;
        //UI::Layout layout(vmm.notify());
        UI::Layout layout;


        Logging::Manager& log_mgr = Logging::Manager::getInstance();

        std::thread logger_thread(&Logging::Manager::run, &log_mgr, 9);

        UI::EventHandler event_handler;


        auto f1 = std::async(&UI::EventHandler::listen, &event_handler, 9);


        if (f1.get() == 0)
        {
            //This will be when exit was called from EventHandler. Then close logger.
            log_mgr.quit();
            logger_thread.join();

            return 0;
        } else return 1;
    }
    catch (const std::logic_error& e)
    {
        std::cerr << "Programming error: " << e.what() << std::endl;

        return -1;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime Error: " << e.what() << std::endl;

        return -1;
    }
    catch (const std::exception& e) { // Catch any other std::exception
        std::cerr << "Caught other std::exception: " << e.what() << std::endl;

        return -1;
    }


    return 0;
}
