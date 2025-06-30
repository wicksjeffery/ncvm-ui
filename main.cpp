// TODO: Do I need to check for memory leak after ctrl-c?

#include "ui/layout.hpp"
#include "ui/event-handler.hpp"
#include "vm/manager.hpp"
#include <future>

int main(/*int argc, char **argv*/)
{
    try
    {
        VM::Manager manager;
        // UI::Layout layout(manager.getState());
        UI::Layout layout;
        UI::EventHandler event_handler;


        auto f1 = std::async(&UI::EventHandler::listen, &event_handler, 9);

        if (f1.get() == 0)
        {
            return 0;
        } else return 1;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
    }





    return 0;
}
