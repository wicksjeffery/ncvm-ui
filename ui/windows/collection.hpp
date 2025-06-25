#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "rectangle.hpp"

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <utility>

namespace UI::Windows
{
    class Collection
    {
        // Private constructor to prevent direct instantiation
        Collection() = default;
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

            return (search != m_windows.end()) ? search->second : throw("bad search y'all");
        }

        void printAll() const
        {
            std::ofstream outputFile;

             outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);

            for (auto const& [key, val] : m_windows)
            {
                outputFile << "key: " << key << std::endl;
            }

             outputFile.close();
        }

        std::pair<std::string, Windows::Rectangle*> findWindow(int y, int x)
        {
            for (const auto& pair : m_windows)
            {
                if (wenclose(pair.second->get_window(), y, x) == true)
                {
                    return pair;
                }

            }

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
