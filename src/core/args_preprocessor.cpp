
#include <iostream>
#include <algorithm>
#include <tuple>

#include <getopt.h>

#include "../libs/args-parser/all.hpp"

#include "args_preprocessor.h"
#include "help_functions.h"

#define ArgData std::tuple<char, std::string, bool, bool, std::string, std::string>



class __AvailableArgs
{
public:
    static std::vector<std::string> __flags;
    static std::vector<ArgData> __data;

};

std::vector<std::string> __AvailableArgs::__flags = {"-f", "-d", "-i", "-t", "-s", "-r", "-V"};
std::vector<ArgData> __AvailableArgs::__data = {
    {'f', "file", true, false, "Path to file", "Specify path to file to open for edit"},
    {'d', "dict", true, false, "Set curent dict to use autocomplete", "Set name for dict"},

    {'i', "install", true, false, "Instal", ""},
    {'t', "tag", true, false, "xPath to container", ""},
    {'s', "site", true, false, "Set site url to parse data", ""},

    {'r', "remove", true, false, "Specify dict name to remove from your computer", ""},
    {'V', "version", false, false, "Show version", ""}
};





ArgsPreprocessor::ArgsPreprocessor() {this->args_info = new ArgsInfo;}


ArgsPreprocessor::~ArgsPreprocessor()
{
    if (this->args_info)
        delete this->args_info;

}


void ArgsPreprocessor::parse(int argc, char** argv)
{
    using namespace Args;

    CmdLine cmd( argc, argv );

    for (ArgData item : __AvailableArgs::__data)
    {
        cmd.addArgWithFlagAndName(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item),
            std::get<3>(item),
            std::get<4>(item),
            std::get<5>(item)
        );

    }
    cmd.addHelp(true, argv[0], "Console editor created just for fun)");

    try {
        cmd.parse();

    }
    catch( const HelpHasBeenPrintedException & )
    {
        exit(0);
    }
    catch( const BaseException & x )
    {
        outStream() << x.desc() << "\n";
        exit(1);
    }


    for (auto item : __AvailableArgs::__flags)
    {
        if (cmd.isDefined(item))
        {
            this->args_info->cmdValues[item] = cmd.value(item);
        } else {
            this->args_info->cmdValues[item] = "$";
        }

    }

}


void ArgsPreprocessor::__show_args_map()
{
    for (auto item : this->args_info->cmdValues)
    {
        std::cout << item.first << " " << item.second << "\n";
    }
    std::cout << "\n";

}


ArgsInfo* ArgsPreprocessor::getArgsInfo() {return this->args_info;}
