#include "ui/layout.hpp"
#include "ui/event_handler.hpp"
#include <future>

int main(/*int argc, char **argv*/)
{
    UI::Layout layout;
    UI::EventHandler events(layout.all_windows);

    auto f1 = std::async(&UI::EventHandler::listen, &events, 9);

    if (f1.get() == 0)
    {
        return 0;
    } else return 1;


    return 0;
}
