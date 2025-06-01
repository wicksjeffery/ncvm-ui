#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
#include <unistd.h>

// Callback function for domain events
void domainEventCallback(virConnectPtr conn, virDomainPtr dom, int event, int detail, void *opaque) {
    char *domainName = virDomainGetName(dom);
    printf("Event: Domain '%s' (%d), Event Type: %d, Detail: %d\n", domainName, virDomainGetID(dom), event, detail);
    free(domainName);
}

// Function to run the libvirt event loop in a separate thread
void *runEventLoop(void *arg) {
    while (1) {
        if (virEventRunDefaultImpl() < 0) {
            fprintf(stderr, "Error running event loop\n");
            break;
        }
    }
    return NULL;
}

int main() {
    virConnectPtr conn;
    pthread_t eventThread;

    // Open a connection to the hypervisor
    conn = virConnectOpen("qemu:///system");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }

    // Register the default event implementation
    if (virEventRegisterDefaultImpl() < 0) {
        fprintf(stderr, "Failed to register event implementation\n");
        virConnectClose(conn);
        return 1;
    }

    // Start the event loop in a separate thread
    if (pthread_create(&eventThread, NULL, runEventLoop, NULL) != 0) {
        fprintf(stderr, "Failed to create event loop thread\n");
        virConnectClose(conn);
        return 1;
    }

    // Register a callback for domain events
    if (virConnectDomainEventRegister(conn, NULL, VIR_DOMAIN_EVENT_ID_LIFECYCLE, domainEventCallback, NULL, NULL) < 0) {
        fprintf(stderr, "Failed to register domain event callback\n");
        virConnectClose(conn);
        return 1;
    }

    printf("Listening for domain events...\n");

    // Keep the program running (you'd typically have your application logic here)
    sleep(60);

    // Unregister the event callback (optional)
    virConnectDomainEventDeregister(conn, domainEventCallback);

    // Clean up
    virConnectClose(conn);
    pthread_cancel(eventThread);
    pthread_join(eventThread, NULL);

    return 0;
}
