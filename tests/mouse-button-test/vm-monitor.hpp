#ifndef VM_MONITOR_HPP
#define VM_MONITOR_HPP

#include "vm-states.hpp"

#include <iostream>
using namespace std;

// bool stop_vm_monitor;



// Watch for new or deleted pid files.
void watch_vm_dir(bool* stop_vm_monitor, VmStates* vm_states);




#endif
