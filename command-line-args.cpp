#include "command-line-args.hpp"
// #include <iostream>

// #include <filesystem>
#include <getopt.h>
// #include <cstdio>
// #include <string>
#include <stdexcept>
// #include <cstring>

CommandLineArgs::CommandLineArgs(int argc, char** argv)
    :
        qemu_pid_dir("/var/run/libvirt/qemu/")
{
    int opt;
    while ((opt = getopt(argc, argv, "t")) != -1) {
        switch (opt) {
            case 't':
                printf("Setting pidfile location to /tmp\n");
                qemu_pid_dir = "/tmp";
                break;
            default:
                throw std::runtime_error("Usage: ncvm -f file -o output\n");
        }
    }
}

CommandLineArgs::~CommandLineArgs()
{}


