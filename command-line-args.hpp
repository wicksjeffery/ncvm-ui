#ifndef COMMAND_LINE_ARGS_HPP
#define COMMAND_LINE_ARGS_HPP

// Journal Entries
enum JE //How much memory could I save if this was a bitfield?
{
    Unset,
    Last,
    New,
    All
} ;

class CommandLineArgs
{
    CommandLineArgs() = default;
    ~CommandLineArgs() = default;

    CommandLineArgs(const CommandLineArgs&) = delete;
    CommandLineArgs& operator=(const CommandLineArgs&) = delete;

    void printHelp();


    JE journal_entries_to_show;


public:
    static CommandLineArgs& getInstance();

    void processArgs(int, char**);



    JE getStartingJournals();
};

#endif
