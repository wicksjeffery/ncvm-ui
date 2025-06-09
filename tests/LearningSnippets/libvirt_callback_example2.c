// Watch status uses callback.
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <stdio.h>


void myErrorFunc(void *userData, virErrorPtr err) {
    fprintf(stderr, "Libvirt Error:\n");
    fprintf(stderr, "  Domain: %d\n", err->domain);
    fprintf(stderr, "  Code: %d\n", err->code);
    fprintf(stderr, "  Message: %s\n", err->message);
    virFreeError(err); // Free the error object
}

int myDomainEventCallback(virConnectPtr conn, virDomainPtr dom,
                          int event, int detail, void *opaque)
{
    const char *eventName;
    switch (event)
    {
        case VIR_DOMAIN_EVENT_DEFINED:
            eventName = "defined";
            break;
        case VIR_DOMAIN_EVENT_UNDEFINED:
            eventName = "undefined";
            break;
        case VIR_DOMAIN_EVENT_STARTED:
            eventName = "started";
            break;
        case VIR_DOMAIN_EVENT_SUSPENDED:
            eventName = "suspended";
            break;
        case VIR_DOMAIN_EVENT_RESUMED:
            eventName = "resumed";
            break;
        case VIR_DOMAIN_EVENT_STOPPED:
            eventName = "stopped";
            break;
        case VIR_DOMAIN_EVENT_SHUTDOWN:
            eventName = "shutdown";
            break;
        case VIR_DOMAIN_EVENT_PMSUSPENDED:
            eventName = "pmsuspended";
            break;
        case VIR_DOMAIN_EVENT_CRASHED:
            eventName = "crashed";
            break;
        // case VIR_DOMAIN_EVENT_LAST:
        //     eventName = "last";
        //     break;
        default:
            eventName = "unknown";
    }

    printf("Domain %s event: %s\n", virDomainGetName(dom), eventName);
    return 0;
}


int main()
{
    virConnectPtr conn;
    virEventRegisterDefaultImpl();

    conn = virConnectOpen("qemu:///system");
    if (!conn) {
        fprintf(stderr, "Failed to open connection\n");
        return 1;
    }

    virSetErrorFunc(NULL, myErrorFunc);
    virConnectDomainEventRegister(conn, myDomainEventCallback, NULL, NULL);

    while (1) {
        virEventRunDefaultImpl(); // Run the event loop
    }

    virConnectClose(conn);
    return 0;
}
