#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "rectangle.hpp"

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>
// #include <vector>

namespace UI::Windows
{
    class Collection
    {
        // Private constructor to prevent direct instantiation
        Collection() = default;
        ~Collection();
        // Delete copy constructor and assignment operator to prevent copying
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;

        std::unordered_map<std::string, Windows::Rectangle*> m_windows;



    public:
        // Static method to get the single instance of Logger
        static Collection& getInstance();

        void insert(const std::string& key, Windows::Rectangle* w)
        {
            m_windows.insert({key, w});
        }

        Windows::Rectangle* find(const std::string& key) const
        {
            auto search = m_windows.find(key);

            return (search != m_windows.end()) ? search->second : throw std::runtime_error("Collection: Key not found.");;
        }

        void printAll() const;


        std::pair<std::string, Windows::Rectangle*> findWindow(int y, int x)
        {
            // printAll();
            // std::ofstream outputFile("/tmp/debug1.txt");

            // std::vector clickable_items;

            for (const auto& pair : m_windows)
            {
                if (wenclose(pair.second->get_window(), y, x) == true)
                {
                    if (pair.first == "UI::Windows::Background" ||
                        pair.first == "UI::Windows::OptionsWindow" ||
                        pair.first == "UI::Windows::Information")
                    {
                        continue;
                    }
                    // Return only if OptionsWindow is hidden or not.
                    // outputFile << "key: " << pair.first << std::endl;
                    return pair;
                }

            }
            // outputFile.close();
            return std::make_pair("", nullptr);
        }

        // std::string print() const
        // {
        //     for (const auto& pair : m_windows) {
        //         return pair.first;
        //     }
        // }
    };
}
#endif
