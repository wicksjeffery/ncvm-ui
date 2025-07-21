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

VM::Manager::Manager()
{
    if (!std::filesystem::exists("ncvm-ui.conf"))
    {
        //TODO send msg to looger to write to systemd journal and ui:
        // no configuration file found. Writing default one...
        // instructions for using config file on about page and github.


        Logging::Manager& log_mgr = Logging::Manager::getInstance();

        log_mgr.write(LOG_ALERT, "Creating default ncvm-ui.conf. Please see \"About\".");


        getVirtualMachines();
    }
}

void VM::Manager::getVirtualMachines()
{
    virConnectPtr conn;
    virDomainPtr *domains;

    size_t i;
    int num_domains;

    // Connect to the hypervisor (e.g., QEMU/KVM)
    conn = virConnectOpen("qemu:///system");
    if (conn == NULL)
    {
        std::stringstream ss;
        ss << "Failed to connect to hypervisor.\n";
        ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

        throw(std::runtime_error(ss.str()));
    }

    unsigned int flags = VIR_CONNECT_LIST_DOMAINS_ACTIVE | VIR_CONNECT_LIST_DOMAINS_INACTIVE;



    num_domains = virConnectListAllDomains(conn, &domains, flags);

    if (num_domains < 0)
        printf("error()");

    if (num_domains == 0)
    {
        std::stringstream ss;
        ss << "No virtual machines found. Create them first.\n";

        throw(std::runtime_error(ss.str()));
    }

    std::ofstream file;
    file.open("ncvm-ui.conf");

    std::string ncvm_ui_conf =
R"(#This is the ncvm-ui configuration file
#
#[vm1]
#vm2      # vm1 won't run if vm2 is mentioned here.
)";

    file << ncvm_ui_conf << std::endl;

    for (i = 0; i < num_domains; i++)
    {
        const char *domain_name;

        domain_name = virDomainGetName(domains[i]);

        // printf("Domain Name: %s, ID: %d, Active: %d, State: %s, Reason: %s\n", domain_name, domain_id, active, state, reason);

         file << '[' << domain_name << ']' << std::endl;
    }

    file << std::endl;
    file.close();


    // Free allocated memory and close the connection
    free(domains);
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
