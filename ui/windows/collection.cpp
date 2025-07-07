#include "collection.hpp"
#include "../logging/manager.hpp"

UI::Windows::Collection& UI::Windows::Collection::getInstance()
{
    // Local static variable, initialized only once and thread-safe since C++11
    static Collection instance;
    return instance;
}




UI::Windows::Collection::~Collection()
{
    for (auto const& [key, val] : m_windows)
    {
        delete val;
    }
}



void UI::Windows::Collection::printAll() const
{
    Logging::Manager& logger = Logging::Manager::getInstance();

    for (auto const& [key, val] : m_windows)
    {
        logger.write(key);
    }
}
