#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <stdio.h>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <string>
#include <vector>
#include <utility> // Required for std::pair

namespace VM
{
    // void errorHandler(void *userdata, virErrorPtr error);

    struct VMState
    {
        // const char* name;
        std::string name;
        int state;
        int reason;
        //TODO cast state and reason to their defines when I use them.
        // virDomainState state;
        // virDomainRunningReason vdrr;

        VMState() = default;

    public:
        VMState(const VMState& other)
            :
                name(other.name),
                state(other.state),
                reason(other.reason)
        {}
        // Declare ClassB as a friend class.
        // This grants all member functions of ClassB access to private_data_A.
        // friend class Manager;

    };

    class Manager
    {
        void getStates();
        void writeConfFile();

        bool config_file_found = true;
        virConnectPtr conn;

        // VMState* tmp_event_vmstate = nullptr;

        std::vector<VMState> vms;
        // std::vector<std::string> vms;

        // void myDomainEventCallback(virConnectPtr conn, virDomainPtr dom,
        //                                         int eventID, int detail, void *opaque)

        bool stop = false;

        int callback_id;

        void validateConfigFile();

        void updateVMwindows();

        const char* getInitialState(int);
        const char* lifycycleEventToString(VMState*);

    public:
        Manager();
        ~Manager();

        void monitorStates(int);

        void quit()
        {
            stop = true;
        }

        // void t()
        // {
            // ClassA a;
            // a.n =3;
        // }

        // void validateSavedConfig();
    };
}



#endif
