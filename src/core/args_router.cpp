
#include <string>

#include "args_router.h"
#include "main_cycle.h"
 


ArgsRouter::ArgsRouter(ArgsInfo* args_info, ConfigReader* config)
{
    this->args_info = args_info;
    this->_config = config;

}


void ArgsRouter::run()
{
    if (this->args_info->mapCounter['f'])
    {
        fmt::print("Open the file {}\n", this->args_info->mapValues['f']);
    
        premGeneralLifeCycle();

    }
    else if (this->args_info->mapCounter['i'])
    {
        fmt::print("Install new dict {}\n", this->args_info->mapValues['i']);
    }
    else if (this->args_info->mapCounter['r'])
    {
        fmt::print("Remove dict {}\n", this->args_info->mapValues['r']);
    }
    else if (this->args_info->mapCounter['V'])
    {
        fmt::print(
            fg(fmt::color::dark_cyan),
            "\tVersion: {}\n\n",
            this->_config->getTableByName("info")["program"]["version"].value_or("Error")
        );

    }
    else if (this->args_info->mapCounter['h'])
    {
        fmt::print(
            fg(fmt::color::dark_cyan),
            "\tVersion: {}\n",
            this->_config->getTableByName("info")["program"]["version"].value_or("Error")
        );

        fmt::print(
            fg(fmt::color::dark_cyan),
            "\n  -f          Specify path to file"
            "\n  -i          Install new dict (need path to folder)"
            "\n  -r          Remove dict by name"
            "\n  -V          Show program version"
            "\n  -h          Show help text"
            "\n\n"
        );

    }

}
