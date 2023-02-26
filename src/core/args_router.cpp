
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

#include <fmt/color.h>
#include <fmt/printf.h>

#include "args_router.h"
#include "main_cycle.h"



ArgsRouter::ArgsRouter(ArgsInfo* args_info, ConfigReader* config)
{
    this->args_info = args_info;
    this->_config = config;

}


void ArgsRouter::run()
{
    if (this->args_info->cmdValues["-f"] != "$")
    {
        premGeneralLifeCycle(this->_config, const_cast<char*>(this->args_info->cmdValues["-f"].c_str()));

    }
    else if (this->args_info->cmdValues["-i"] != "$")
    {
        fmt::print("TODO: Install new dict {}\n", this->args_info->cmdValues["-i"]);
    }
    else if (this->args_info->cmdValues["-r"] != "$")
    {
        fmt::print("TODO: Remove dict {}\n", this->args_info->cmdValues["-r"]);
    }
    else if (this->args_info->cmdValues["-V"] != "$")
    {
        fmt::print(
            fg(fmt::color::dark_cyan),
            "\tVersion: {}\n\n",
            this->_config->getTableByName("info")["program"]["version"].value_or("Error")
        );

    }

}
