#include "command-line-args.hpp"
#include <getopt.h>
#include <stdexcept>
#include <iostream>
#include <sstream>

// reference: https://gist.github.com/ashwin/d88184923c7161d368a9


void CommandLineArgs::printHelp()
{

    std::string help =
R"(
Usage: ncvm-ui [OPTION]

-j, --journals=<STRING>     Journal entries to show upon start:
                            [all, new, last] (default is: last)
-h, --help                  Print this help";
)";

    std::cout << help << std::endl;

    exit(1);
}

CommandLineArgs& CommandLineArgs::getInstance()
{
    static CommandLineArgs instance;
    return instance;
}



void CommandLineArgs::processArgs(int argc, char** argv)
{
    /**
     * @brief Run once.
     *
     * Ensure this function only runs once.
     */
    if (journal_entries_to_show != Unset)
    {
        std::stringstream ss;
        ss << "cmdline args have already been parsed.\n";
        ss << __FILE_NAME__ << ": " << __PRETTY_FUNCTION__ << std::endl;

        throw(std::logic_error(ss.str()));
    }
    else journal_entries_to_show = Last;


    const char* const short_opts = "j:h";
    const option long_opts[] =
    {
        {"journals", required_argument, nullptr, 'j'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {

            case 'j':
            {
                std::string je(optarg);
                if (je == "last")
                {
                    journal_entries_to_show = Last;
                }
                else if (je == "new")
                {
                    journal_entries_to_show = New;
                }
                else if (je == "all")
                {
                    journal_entries_to_show = All;
                }
                else printHelp();

                break;
            }
            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                printHelp();
                break;
        }
    }
}

JE CommandLineArgs::getStartingJournals()
{
    return journal_entries_to_show;
}

