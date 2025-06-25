#include "collection.hpp"

UI::Windows::Collection& UI::Windows::Collection::getInstance()
{
    // Local static variable, initialized only once and thread-safe since C++11
    static Collection instance;
    return instance;
}
