#include "ui/layout.hpp"
#include "ui/event-handler.hpp" //TODO fix typo in name
#include <future>

int main(/*int argc, char **argv*/)
{
    try
    {
        UI::Layout layout;
        // UI::EventHandler events(&layout.all_windows);
        UI::EventHandler event_handler;
        // UI::Layout layout(event_handler.m_windows);


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
