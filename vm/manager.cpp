#include "manager.hpp"
#include "windows/collection.hpp"

#include <fstream>
#include <filesystem>
#include <array>

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
#include <error.h>

VM::Manager::Manager()
{
    if (!std::filesystem::exists("ncvm-ui.conf"))
    {
        //TODO send msg to looger to write to systemd journal and ui:
        // no configuration file found. Writing default one...
        // instructions for using config file on about page and github.

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

    std::ofstream outputFile;
    // outputFile.open("/tmp/debug.txt", std::ofstream::out | std::ofstream::app);
    outputFile.open("/tmp/debug.txt");

    for (i = 0; i < num_domains; i++)
    {
        const char *domain_name;

        domain_name = virDomainGetName(domains[i]);

        // printf("Domain Name: %s, ID: %d, Active: %d, State: %s, Reason: %s\n", domain_name, domain_id, active, state, reason);

        outputFile << domain_name << std::endl;
    }

    outputFile.close();


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
