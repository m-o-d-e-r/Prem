
#include <iostream>
#include <algorithm>

#include <fmt/printf.h>
#include <fmt/color.h>

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


static bool __is_correct_key_format(char* __str, int __len)
{
    int m_count = std::count(__str, __str + __len, '-');


    if (m_count > 2 || m_count == 0)
        return false;

    if (__str[0] == '-' && __str[1] == '-')
        return true;

    if (m_count == 2 && (__str[0] != '-' || __str[1] != '-'))
        return false;
 
    if (m_count == 1 && __str[0] != '-')
        return false;


    return true;
}




ArgsPreprocessor::ArgsPreprocessor()
{
    // TODO: raise an exception
}


ArgsPreprocessor::ArgsPreprocessor(int argc, char** argv)
{
    // TODO: raise an exception if count if args is equal to 1


    this->argc = argc;
    this->argv = argv;
}


int ArgsPreprocessor::parse()
{
    bool __has_error = false;

    bool __curr;
    bool __next;


    int __summary_length = __get_length(argv[0]) + 1;
    for (int i = 1; i < argc; i++)
    {
        __summary_length += __get_length(argv[i]) + 1;

        __curr = __is_correct_key_format(argv[i], __get_length(argv[i]));

        if (i != argc - 1)
            __next = __is_correct_key_format(argv[i + 1], __get_length(argv[i + 1]));
        else
            __next = true;


        if (__curr & __next)
        {
            this->__args_map[argv[i]] = "";
        } else if (__curr & !__next)
        {
            this->__args_map[argv[i]] = argv[i + 1];
        } else if (!__curr & !__next)
        {
            __has_error = true;


            fmt::print(
                fg(fmt::color::dark_cyan),
                "\n  {}\n",
                fmt::join(argv, argv + argc, " ")
            );

            fmt::print(
                fg(fmt::color::orange_red),
                "{:>{}}\n", "^",
                __summary_length + 2
            );

            fmt::print(
                fg(fmt::color::orange_red),
                "\tBad args ({}, {})\n",
                argv[i], argv[i + 1]
            );

            fmt::print("  {:->20}\n", "-");

        }

    }


    if (__has_error)
    {
        __show_args_map();
        return -1;
    }

    return 0;

}


void ArgsPreprocessor::__show_args_map()
{
    std::map<std::string, std::string>::iterator args_map_it;


    fmt::print(
        fg(fmt::color::dark_cyan),
        "\n{:^40}\n",
        "Recognized arguments"
    );

    for (args_map_it = this->__args_map.begin(); args_map_it != this->__args_map.end(); args_map_it++)
    {
        fmt::print(
            "  {}: {}\n",
            args_map_it->first, args_map_it->second
        );
    }

    fmt::print("\n");

}


std::map<std::string, std::string> ArgsPreprocessor::getArgs()
{
    return this->__args_map;    
}
