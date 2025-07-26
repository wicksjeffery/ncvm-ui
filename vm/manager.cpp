#include "manager.hpp"
#include "windows/collection.hpp"

#include <fstream>
#include <filesystem>
#include <array>
#include "../logging/manager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
#include <error.h>
#include <syslog.h>

#include <libvirt/libvirt-event.h>
#include <regex>

/*
TODO if libvirt errors need to be non-fatal then
Use a Lambda or std::bind: If virSetErrorFunc needs to access object-specific data,
use a C++11 lambda or std::bind to capture this and create a callable object that can
be passed as a callback.

Because, perhaps restarting the app is better than allowing the problem to be resolved
from within the app.
*/
namespace
{
    void errorHandler(void *userdata, virErrorPtr error)
    {
        if (error != NULL)
        {
            std::stringstream ss;
            ss << "libvirt error\n";
            ss << "Domain:" << error->domain << std::endl;
            ss << "Code:" << error->code << std::endl;
            ss << "Message:" << error->message << std::endl;
            ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

            throw(std::runtime_error(ss.str()));
        }
    }



    // std::string event_thing;
    // int event_n;

    VM::VMState* tmp_vmstate = nullptr;
    // VM::VMState tmp_vmstate ;

    void myDomainEventCallback(virConnectPtr conn,
                               virDomainPtr dom,
                               int eventID,
                               int detail,
                               VM::VMState *opaque)
    {
        tmp_vmstate = new VM::VMState;

        if (dom != nullptr)
        {
            // printf("  Domain Name: %s\n", virDomainGetName(dom));
            // event_thing += "  Domain Name:";
            // event_thing += virDomainGetName(dom);

            tmp_vmstate->name = virDomainGetName(dom);
            // tmp_vmstate.name = virDomainGetName(dom);
        }
        else
        {
            tmp_vmstate->name = "nullptr!"; //Not sure if this could ever happen.
        }

        tmp_vmstate->state = eventID;
        tmp_vmstate->reason = detail;

        // event_thing = " event_thing(";
        // event_thing += std::to_string(eventID);
        // event_thing += ").";
        // printf("Domain event received: ");
        // event_thing += "Domain event received: ";

        // if (eventID == VIR_DOMAIN_EVENT_ID_LIFECYCLE)
        // {
        //     event_thing = " VIR_DOMAIN_EVENT_ID_LIFECYCLE";
        // } else
        // {
        //    event_thing += " eventID: ";
        //    event_thing += std::to_string(eventID);
        //    event_thing += " detail: ";
        //    event_thing += std::to_string(detail);
        // }

        // switch (eventID)
        // {
        //     case VIR_DOMAIN_EVENT_DEFINED:
        //         // printf("DEFINED)\n");
        //         tmp_vmstate.state = "DEFINED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_UNDEFINED:
        //         // printf("DEFINED)\n");
        //         tmp_vmstate.state = "UNDEFINED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_STARTED:
        //         // printf("STARTED)\n");
        //         tmp_vmstate.state = "STARTED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_SUSPENDED:
        //         // printf("SUSPENDED)\n");
        //         tmp_vmstate.state = "SUSPENDED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_RESUMED:
        //         // printf("RESUMED)\n");
        //         tmp_vmstate.state = "RESUMED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_STOPPED:
        //         // printf("STOPPED)\n");
        //         tmp_vmstate.state = "STOPPED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_SHUTDOWN:
        //         // printf("SHUTDOWN)\n");
        //         tmp_vmstate.state = "SHUTDOWN)";
        //         break;
        //     case VIR_DOMAIN_EVENT_PMSUSPENDED:
        //         // printf("PM_SUSPENDED)\n");
        //         tmp_vmstate.state = "PM_SUSPENDED)";
        //         break;
        //     case VIR_DOMAIN_EVENT_CRASHED:
        //         // printf("CRASHED)\n");
        //         tmp_vmstate.state = "CRASHED)";
        //         break;
        //     default:
        //         // printf("UNKNOWN_DETAIL %d)\n", detail);
        //         tmp_vmstate.state = "UNKNOWN_DETAIL)";
        //         break;
        // }


        // if (dom != NULL)
        // if (dom != nullptr)
        // {
        //     // printf("  Domain Name: %s\n", virDomainGetName(dom));
        //     // event_thing += "  Domain Name:";
        //     // event_thing += virDomainGetName(dom);
        //     tmp_vmstate.name = virDomainGetName(dom);
        // }
    }
}

VM::Manager::Manager()
{
    // if (!std::filesystem::exists("ncvm-ui.conf"))
    // {
    //     //TODO send msg to looger to write to systemd journal and ui:
    //     // no configuration file found. Writing default one...
    //     // instructions for using config file on about page and github.
    //
    //
    //     Logging::Manager& log_mgr = Logging::Manager::getInstance();
    //
    //     log_mgr.write(LOG_ALERT, "Creating default ncvm-ui.conf. Please see \"About\".");
    //
    //     config_file_found = false;
    // }

    getStates();

    // if (!config_file_found)
    // {
    //     writeConfFile();
    //
    //     config_file_found = true;
    // }
}

void VM::Manager::validateConfigFile()
{
    if (std::filesystem::exists("ncvm-ui.conf"))
    {
        std::ifstream file("ncvm-ui.conf");

        std::string line;
        int line_number = 0;

        std::vector<std::string> list_of_vms_to_show; // In case there are more than 4. TODO test this

        while (std::getline(file, line))
        {
            // Get the vm name from between the brackets.
            if (std::regex_search(line, std::regex("^\\[\\w+\\].*")))
            {
                bool item_found = false;
                // Then make sure this vm is found in the list of active vm's.
                for (const auto& vm : vms)
                {
                    if (vm.name == line.substr(1, (line.length()-2) ))
                    {
                        // std::cout << "vm " << vm.name << std::endl;
                        item_found = true;

                        list_of_vms_to_show.push_back(vm.name);
                        break;
                    }
                }

                line_number++;
                if (!item_found)
                {
                    std::stringstream ss;
                    ss << "VM name in ncvm-ui.conf doesn't match (line " << line_number << ")\n";
                    ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

                    throw(std::runtime_error(ss.str()));
                }
            }
        }

        file.close();

        // Any vm's not on the list gets removed from the vms collection.
        // maybe consider erase if not found:
        /*
        vec.erase(std::remove_if(vec.begin(), vec.end(), [](int n) {
            return n % 2 == 0;
        }), vec.end());
        */
        for (auto it = vms.begin(); it != vms.end(); )
        {
            bool not_found = true;
            for (const auto& vm_name : list_of_vms_to_show)
            {
                if (it->name == vm_name)
                {
                    //Then keep it.
                    not_found = false;
                }
            }

            if (not_found)
            {
                it = vms.erase(it);
            }
            else ++it;
        }

        // std::cout << "size: " << vms.size() << std::endl;
        // for (const auto& vm : vms)
        // {
        //
        //     std::cout << "keeping: " << vm.name << std::endl;
        // }
    }
    else
    {
        //TODO send msg to looger to write to systemd journal and ui:
        // no configuration file found. Writing default one...
        // instructions for using config file on about page and github.
        Logging::Manager& log_mgr = Logging::Manager::getInstance();

        log_mgr.write(LOG_ALERT, "Creating default ncvm-ui.conf. Please see \"About\".");


        std::ofstream file("ncvm-ui.conf");
        if (!file.is_open())
        {
            std::stringstream ss;
            ss << "Failed to open ncvm_ui_conf.\n";
            ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

            throw(std::runtime_error(ss.str()));
        }

        file << "# This is the ncvm-ui configuration file" << std::endl;
        file << "#" << std::endl;
        file << "# [vm1]" << std::endl;
        file << "# vm2      # vm1 won't run if vm2 is mentioned here.\n" << std::endl;

        int size = vms.size();

        for (int i=0; i < 4; i++)
        {
            if (i < size)
            {
                file << '[' <<  vms[i].name << "]\n" << std::endl;
            }
            // else // Create placeholders for the remaining slots.
            // {
            //     file << "[]\n" << std::endl;
            // }
        }


        file.close();
    }
}


void VM::Manager::writeConfFile()
{
//     std::ofstream file;
//     file.open("ncvm-ui.conf");
//
//     std::string ncvm_ui_conf =
// R"(# This is the ncvm-ui configuration file
// #
// # [vm1]
// # vm2      # vm1 won't run if vm2 is mentioned here.
// )";
//
//     file << ncvm_ui_conf << std::endl;


    // for (const VMState& vm : vms)
    // for (auto vm : vms)
    // {
    //     file << '[' << vm.name << "]\n" << std::endl;
    //     file << "state: " << vm.state << std::endl;
    //     file << "reason: " << vm.reason << std::endl;
    //
    // }
    //
    // file << std::endl;
    // file.close();
}

const char* VM::Manager::getInitialState(int state)
{
    switch (state)
    {
        case VIR_DOMAIN_NOSTATE: return "nostate";
        case VIR_DOMAIN_RUNNING: return "running";
        case VIR_DOMAIN_BLOCKED: return "blocked";
        case VIR_DOMAIN_PAUSED: return "paused";
        case VIR_DOMAIN_SHUTDOWN: return "shutdown";
        case VIR_DOMAIN_SHUTOFF: return "shutoff";
        case VIR_DOMAIN_CRASHED: return "crashed";
        case VIR_DOMAIN_PMSUSPENDED: return "suspended";
        default: return "unknown";
    }
}

const char * VM::Manager::lifycycleEventToString(VMState* v)
{
    unsigned vm_number = 0;
    std::string event_state;
    for (auto& vm : vms)
    {
        vm_number++;
        // Do something if the event was generated from one of the machines,
        // we're watching.
        if (v->name == vm.name)
        {
            vm.state = v->state; //TODO do I only care to save the machine name?
            vm.reason = v->reason; //Maybe not neccessary to save state and reason past this function.

            switch (v->state)
            {
                case VIR_DOMAIN_EVENT_DEFINED:
                    event_state = " defined: ";
                    break;
                case VIR_DOMAIN_EVENT_UNDEFINED:
                    event_state = " undefined: ";
                    break;
                case VIR_DOMAIN_EVENT_STARTED:
                    event_state = " started: ";
                    break;
                case VIR_DOMAIN_EVENT_SUSPENDED:
                    event_state = " suspended: ";
                    break;
                case VIR_DOMAIN_EVENT_RESUMED:
                    event_state = " resumed: ";
                    break;
                case VIR_DOMAIN_EVENT_STOPPED:
                    event_state = " stopped: ";
                    break;
                case VIR_DOMAIN_EVENT_SHUTDOWN:
                    event_state = " shutdown: ";
                    break;
                case VIR_DOMAIN_EVENT_PMSUSPENDED:
                    event_state = " pm_suspended: ";
                    break;
                case VIR_DOMAIN_EVENT_CRASHED:
                    event_state = " crashed: ";
                    break;
                default:
                    event_state = " error: ";
                    break;
            }

            event_state.append(std::to_string(v->reason));

            switch (vm_number)
            {
                case 1:
                {

                    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
                    WINDOW* win = collection.find("UI::Windows::VMControl::One")->get_window();
                    int max_x = getmaxx(collection.find("UI::Windows::VMControl::One")->get_window()); // Get the maximum column of the window.
                    if (event_state.length() > max_x-4) //TODO think if this is right thing to do here.
                    {
                        event_state.resize(max_x-4);
                        event_state.append("~");
                    }

                    wattron(win, COLOR_PAIR(3) | A_BOLD);
                    mvwhline(win, 5, 1, ' ', max_x-2); //Clear the line.
                    wmove(win, 5, 1);
                    waddch(win, ACS_RARROW);
                    wprintw(win, "%s", event_state.c_str());
                    wattroff(win, COLOR_PAIR(3) | A_BOLD);
                    wrefresh(win);
                }
                case 2:
                {

                    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
                    WINDOW* win = collection.find("UI::Windows::VMControl::Two")->get_window();
                    int max_x = getmaxx(collection.find("UI::Windows::VMControl::Two")->get_window()); // Get the maximum column of the window.
                    if (event_state.length() > max_x-4) //TODO think if this is right thing to do here.
                    {
                        event_state.resize(max_x-4);
                        event_state.append("~");
                    }

                    wattron(win, COLOR_PAIR(3) | A_BOLD);
                    mvwhline(win, 5, 1, ' ', max_x-2); //Clear the line.
                    wmove(win, 5, 1);
                    waddch(win, ACS_RARROW);
                    wprintw(win, "%s", event_state.c_str());
                    wattroff(win, COLOR_PAIR(3) | A_BOLD);
                    wrefresh(win);
                }
                case 3:
                {

                    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
                    WINDOW* win = collection.find("UI::Windows::VMControl::Three")->get_window();
                    int max_x = getmaxx(collection.find("UI::Windows::VMControl::Three")->get_window()); // Get the maximum column of the window.
                    if (event_state.length() > max_x-4) //TODO think if this is right thing to do here.
                    {
                        event_state.resize(max_x-4);
                        event_state.append("~");
                    }

                    wattron(win, COLOR_PAIR(3) | A_BOLD);
                    mvwhline(win, 5, 1, ' ', max_x-2); //Clear the line.
                    wmove(win, 5, 1);
                    waddch(win, ACS_RARROW);
                    wprintw(win, "%s", event_state.c_str());
                    wattroff(win, COLOR_PAIR(3) | A_BOLD);
                    wrefresh(win);
                }
                case 4:
                {

                    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();
                    WINDOW* win = collection.find("UI::Windows::VMControl::Four")->get_window();
                    int max_x = getmaxx(collection.find("UI::Windows::VMControl::Four")->get_window()); // Get the maximum column of the window.
                    if (event_state.length() > max_x-4) //TODO think if this is right thing to do here.
                    {
                        event_state.resize(max_x-4);
                        event_state.append("~");
                    }

                    wattron(win, COLOR_PAIR(3) | A_BOLD);
                    mvwhline(win, 5, 1, ' ', max_x-2); //Clear the line.
                    wmove(win, 5, 1);
                    waddch(win, ACS_RARROW);
                    wprintw(win, "%s", event_state.c_str());
                    wattroff(win, COLOR_PAIR(3) | A_BOLD);
                    wrefresh(win);
                }
            }
        }
    }

    return "";

}


#include <ncurses.h>
void VM::Manager::updateVMwindows()
{
    UI::Windows::Collection& collection = UI::Windows::Collection::getInstance();

    //TODO compare to all other vms to see if truncating will result in identical names. Then adjust.
    std::string truncated_vm_name;

    int max_x = getmaxx(collection.find("UI::Windows::VMControl::One")->get_window()); // Get the maximum column of the window.
    // const char* vm_name_tmp = "Fedora";
    // int text_len = strlen(vm_name_tmp); // Get the length of the text.
    // int start_col = (max_x - text_len) / 2; // Calculate the starting column.

    int start_col;


    switch (vms.size()) //TODO put this in a for loop so machine names are not in reverse order
    {
        case 4:
            truncated_vm_name = vms[3].name;
            if (truncated_vm_name.length() > max_x-5)
            {
                truncated_vm_name.resize(12);
                truncated_vm_name.append("~");
            }

            start_col = (max_x - truncated_vm_name.length()) / 2;

            mvwprintw(collection.find("UI::Windows::VMControl::Four")->get_window(), 2, start_col, "%s", truncated_vm_name.c_str());
            wrefresh(collection.find("UI::Windows::VMControl::Four")->get_window());
            // break;
        case 3:
            truncated_vm_name = vms[2].name;
            if (truncated_vm_name.length() > max_x-5)
            {
                truncated_vm_name.resize(12);
                truncated_vm_name.append("~");
            }

            start_col = (max_x - truncated_vm_name.length()) / 2;

            mvwprintw(collection.find("UI::Windows::VMControl::Three")->get_window(), 2, start_col, "%s", truncated_vm_name.c_str());
            wrefresh(collection.find("UI::Windows::VMControl::Three")->get_window());
            // break;
        case 2:
            truncated_vm_name = vms[1].name;
            if (truncated_vm_name.length() > max_x-5)
            {
                truncated_vm_name.resize(12);
                truncated_vm_name.append("~"); //TODO test this with a long vm name
            }

            start_col = (max_x - truncated_vm_name.length()) / 2;

            mvwprintw(collection.find("UI::Windows::VMControl::Two")->get_window(), 2, start_col, "%s", truncated_vm_name.c_str());
            wrefresh(collection.find("UI::Windows::VMControl::Two")->get_window());
            // break;
        case 1:
            truncated_vm_name = vms[0].name;
            if (truncated_vm_name.length() > max_x-5)
            {
                truncated_vm_name.resize(12);
                truncated_vm_name.append("~"); //TODO test this with a long vm name
            }

            start_col = (max_x - truncated_vm_name.length()) / 2;

            WINDOW* win = collection.find("UI::Windows::VMControl::One")->get_window();


            mvwprintw(win, 2, start_col, "%s", truncated_vm_name.c_str());

            std::stringstream ss;

            // ss << " s" << vms[0].state << ": " << vms[0].reason;
            ss << " " << getInitialState(vms[0].state) << ": " << vms[0].reason;

            // INFO: in the unknown even that the string is longer than the
            // available space, truncate it so it doesn't write out of the
            // window.
            std::string tmp = ss.str();
            if (tmp.length() > max_x-4)
            {
                tmp.resize(max_x-4);
                tmp.append("~");
            }

            wattron(win, COLOR_PAIR(3) | A_BOLD);
            mvwhline(win, 5, 1, ' ', max_x-2); //Clear the line.
            wmove(win, 5, 1);
            waddch(win, ACS_RARROW);
            wprintw(win, "%s", tmp.c_str());
            wattroff(win, COLOR_PAIR(3) | A_BOLD);
            wrefresh(win);
    }
}


void VM::Manager::getStates()
{
    // virConnectPtr conn;
    // Set the custom error handler
    // virSetErrorFunc(nullptr, errorHandler);
    virDomainPtr *domains;

    size_t i;
    int num_domains;

    virEventRegisterDefaultImpl(); //For event loop

    // Connect to the hypervisor (e.g., QEMU/KVM)
    conn = virConnectOpen("qemu:///system");
    if (conn == NULL)
    {
        std::stringstream ss;
        ss << "Failed to connect to hypervisor.\n";
        ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

        throw(std::runtime_error(ss.str()));
    }

    virSetErrorFunc(nullptr, errorHandler);

    unsigned int flags = VIR_CONNECT_LIST_DOMAINS_ACTIVE | VIR_CONNECT_LIST_DOMAINS_INACTIVE;

    num_domains = virConnectListAllDomains(conn, &domains, flags);

    if (num_domains < 0)
    {
        std::stringstream ss;
        ss << "Error: call to virConnectListAllDomains()\n";
        ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

        throw(std::runtime_error(ss.str()));
    }

    if (num_domains == 0)
    {
        std::stringstream ss;
        ss << "No virtual machines found. Create them first.\n";

        throw(std::runtime_error(ss.str()));
    }

    for (i = 0; i < num_domains; i++)
    {
        VMState vm_state;

        vm_state.name = virDomainGetName(domains[i]);

        virDomainGetState(domains[i], &vm_state.state, &vm_state.reason, 0);

        vms.push_back(vm_state);


        virDomainFree(domains[i]);
    }

    validateConfigFile();
    updateVMwindows(); //After this, we're up and running. Next start listening for events.'

    // int eventID;
    // virConnectClose(conn);
    // int ret = virConnectDomainEventRegister(conn, myDomainEventCallback, NULL, NULL); //Register event callback
    callback_id = virConnectDomainEventRegisterAny(conn,
                                                   NULL,
                                                   VIR_DOMAIN_EVENT_ID_LIFECYCLE,
                                                   (virConnectDomainEventGenericCallback)myDomainEventCallback,
                                                   // NULL,
                                                   tmp_vmstate,
                                                   NULL); //Register event callback

    if (callback_id < 0)
    {
        std::stringstream ss;
        ss << "Error: call to virConnectListAllDomains()\n";
        ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

        throw(std::runtime_error(ss.str()));
    }
}



void VM::Manager::monitorStates(int n)
{

    while (stop == false)
    {
        virEventRunDefaultImpl(); // Run the event loop

        if (tmp_vmstate != nullptr)
        {
            // VMState v  = *tmp_vmstate;
            lifycycleEventToString(tmp_vmstate);

            // Logging::Manager& log_mgr = Logging::Manager::getInstance();
            // log_mgr.write(LOG_CRIT, tmp_vmstate->name.c_str());

            delete tmp_vmstate;
            tmp_vmstate = nullptr;
        }
    }

    // Deregister the callback (should be done before closing connection)
    if (virConnectDomainEventDeregisterAny(conn, callback_id) < 0)
    {
        std::stringstream ss;
        ss << "Failed to deregister domain event callback.\n";
        ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

        throw(std::runtime_error(ss.str()));
    }
}

VM::Manager::~Manager()
{
    virConnectClose(conn);
}



// void VM::Manager::validateSavedConfig()
// {
//     if (!std::filesystem::exists("ncvm-ui.conf"))
//     {
//
//     }
//
//     // std::ofstream outputFile("/tmp/debug.txt");
// }
