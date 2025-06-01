#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
#include <error.h>


int main() {
    virConnectPtr conn;
    virDomainPtr *domains;

    size_t i;
    int num_domains;

    // Connect to the hypervisor (e.g., QEMU/KVM)
    conn = virConnectOpen("qemu:///system");
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to hypervisor\n");
        return 1;
    }

    unsigned int flags = \
    VIR_CONNECT_LIST_DOMAINS_RUNNING | \
    VIR_CONNECT_LIST_DOMAINS_PAUSED | \
    VIR_CONNECT_LIST_DOMAINS_SHUTOFF;



    num_domains = virConnectListAllDomains(conn, &domains, flags);
    // printf("ret: %d", num_domains);
    if (num_domains < 0)
        printf("error()");

    // Loop through each domain and print its name and ID
    for (i = 0; i < num_domains; i++) {
        const char *domain_name;
        unsigned int domain_id;

        domain_name = virDomainGetName(domains[i]);
        domain_id = virDomainGetID(domains[i]);
        printf("Domain Name: %s, ID: %d\n", domain_name, domain_id);
    }

    // Free allocated memory and close the connection
    free(domains);
    virConnectClose(conn);
    return 0;
}

