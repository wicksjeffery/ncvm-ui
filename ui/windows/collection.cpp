#include "collection.hpp"

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
