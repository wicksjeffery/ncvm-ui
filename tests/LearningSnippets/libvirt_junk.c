#include <stdio.h>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

typedef virError * virErrorPtr;
// void myErrorFunc(void *userData, virErrorPtr err = NULL) {
//     fprintf(stderr, "Libvirt error: %s\n", err->message);
//     virFreeError(err); // Free the error object
// }

void myErrorHandler(void *userdata, virErrorPtr err) {
    if (err != NULL) {
        fprintf(stderr, "Libvirt Error:\n");
        fprintf(stderr, "  Domain: %d\n", err->domain);
        fprintf(stderr, "  Code: %d\n", err->code);
        fprintf(stderr, "  Message: %s\n", err->message);
    }
}


int main()
{
    // Set the custom error handling function
    virSetErrorFunc(NULL, myErrorHandler);

    return 0;
}
