#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include "rectangle.hpp"

#include <string>
#include <unordered_map>


namespace UI
{
    class Layout
    {
    public:
        // std::vector<const Windows::Rectangle*> all_windows;
        //TODO make this private:
        std::unordered_map<std::string, const Windows::Rectangle*> all_windows;

        // void save_window(const UI::Windows::Rectangle* rect)
        // {
        //     all_windows.push_back(rect);
        // }

    public:
        Layout();
        ~Layout();
    };
}
#endif
