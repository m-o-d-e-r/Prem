
#include <iostream>
#include <algorithm>

#include "args_preprocessor.h"




ArgsPreprocessor::ArgsPreprocessor()
{
    this->args_info = new gengetopt_args_info;

}


ArgsPreprocessor::~ArgsPreprocessor()
{
    if (this->args_info)
        delete this->args_info;

}


void ArgsPreprocessor::parse(int argc, char** argv)
{
    if (cmdline_parser (argc, argv, this->args_info) != 0)
        exit(1);

}


void ArgsPreprocessor::__show_args_map() {}


gengetopt_args_info* ArgsPreprocessor::getArgsTable() {return this->args_info;}
