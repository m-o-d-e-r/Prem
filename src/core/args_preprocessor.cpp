
#include <iostream>
#include <algorithm>

#include <getopt.h>

#include "args_preprocessor.h"



static int __get_length(char* __str)
{
    int __len = 0;

    while (true)
    {
        if (__str[__len] != '\0')
            __len++;
        else
            break;
    }

    return __len;
}


static void __print_error_pointer(int argc, char** argv)
{
    int _global_cli_length = 0;


    fmt::print("\n");

    for (int i = 0; i < argc; i++)
    {
        if (i < optind)
            _global_cli_length += __get_length(argv[i]) + 1;

        fmt::print(
            fg(fmt::color::dark_cyan),
            "{} ",
            argv[i]
        );

    }

    fmt::print(
        fg(fmt::color::orange_red),
        "\n{:>{}}\n",
        "^",
        _global_cli_length - 1
    );


}


static void __double_definition_check(ArgsInfo* args_info, char option, int argc, char** argv)
{
    if (!args_info->mapCounter[option])
    {
        args_info->mapCounter[option]++;
        args_info->mapValues[option] = optarg;
    } else {
        __print_error_pointer(argc, argv);

        fmt::print(
            fg(fmt::color::orange_red),
            "\targs preprocessor: detected double definition -- '{}'\n\n",
            option
        );
        exit(2);
    }
}


static void __one_cli_argument_check(ArgsInfo* args_info, char option, int argc, char** argv)
{
    std::map<char, uint8_t>::iterator _map_iterator = args_info->mapCounter.begin();

    for (; _map_iterator != args_info->mapCounter.end(); _map_iterator++)
    {
        if (_map_iterator->first == option)
            continue;

        if (_map_iterator->second)
        {
            __print_error_pointer(argc, argv);

            fmt::print(
                fg(fmt::color::orange_red),
                "\targs preprocessor: bad argument usage. (Usage: prem [Option]) you can use only one allowed key\n\n"
            );
            exit(2);
        }
    }
}



ArgsPreprocessor::ArgsPreprocessor() {this->args_info = new ArgsInfo;}


ArgsPreprocessor::~ArgsPreprocessor()
{
    if (this->args_info)
        delete this->args_info;

}


void ArgsPreprocessor::parse(int argc, char** argv)
{
    int _opt;
    int _iteration = 0;


    while((_opt = getopt(argc, argv, ":f:i:r:Vh")) != -1)
    {
        switch(_opt)
        {
        case 'f':
            __double_definition_check(this->args_info, 'f', argc, argv);
            __one_cli_argument_check(this->args_info, 'f', argc, argv);
            break;

        case 'i':
            __double_definition_check(this->args_info, 'i', argc, argv);
            __one_cli_argument_check(this->args_info, 'i', argc, argv);
            break;

        case 'r':
            __double_definition_check(this->args_info, 'r', argc, argv);
            __one_cli_argument_check(this->args_info, 'r', argc, argv);
            break;

        case 'V':
            __double_definition_check(this->args_info, 'V', argc, argv);
            __one_cli_argument_check(this->args_info, 'V', argc, argv);
            break;

        case 'h':
            __double_definition_check(this->args_info, 'h', argc, argv);
            __one_cli_argument_check(this->args_info, 'h', argc, argv);
            break;

        /*case 'g':
            __double_definition_check(this->args_info, 'g', argc, argv);
            __one_cli_argument_check(this->args_info, 'g', argc, argv);
            break;*/

        case '?':
            __print_error_pointer(argc, argv);

            fmt::print(
                fg(fmt::color::orange_red),
                "\targs preprocessor: invalid option -- '{}'\n\n",
                (char)optopt
            );
            exit(2);
            break;

        case ':':
            __print_error_pointer(argc, argv);

            fmt::print(
                fg(fmt::color::orange_red),
                "\targs preprocessor: option requires an argument -- '{}'\n\n",
                (char)optopt
            );
            exit(2);
            break;

        }

    }


    /*if (cmdline_parser (argc, argv, this->args_info) != 0)
        exit(1);*/

}


void ArgsPreprocessor::__show_args_map() {}


ArgsInfo* ArgsPreprocessor::getArgsInfo() {return this->args_info;}
