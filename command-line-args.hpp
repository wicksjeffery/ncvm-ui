#ifndef COMMAND_LINE_ARGS_HPP
#define COMMAND_LINE_ARGS_HPP


class CommandLineArgs
{
    const char* qemu_pid_dir;

public:
    CommandLineArgs(int argc, char** argv);
    ~CommandLineArgs();

    const char* getPIDFileDir()
    {
        return qemu_pid_dir;
    }
};

#endif
