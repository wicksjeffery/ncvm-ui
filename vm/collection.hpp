#ifndef VM_COLLECTION_HPP
#define VM_COLLECTION_HPP



#include <string>
#include <unordered_map>
#include <iostream>

#include <utility>


namespace VM
{
    class Collection
    {
        // Private constructor to prevent direct instantiation
        Collection() = default;
        // ~Collection();
        // Delete copy constructor and assignment operator to prevent copying
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;

        std::unordered_map<std::string, std::string> m_vms;



    public:
        // Static method to get the single instance of Logger
        static Collection& getInstance();

        void insert(const std::string& key, std::string state)
        {
            m_vms.insert({key, state});
        }

        std::string find(const std::string& key) const
        {
            auto search = m_vms.find(key);

            return (search != m_vms.end()) ? search->second : throw std::runtime_error("VM::Collection: Key not found.");;
        }

        // void printAll();
    };
}
#endif
