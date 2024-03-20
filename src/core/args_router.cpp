
#include <fmt/printf.h>
#include <fmt/color.h>   

#include "args_router.h"
#include "main_cycle.h"
 


ArgsRouter::ArgsRouter(gengetopt_args_info* args_info)
{
    this->args_info = args_info;

}

void ArgsRouter::run()
{
    if (this->args_info->file_arg)
    {
       fmt::print("Open the file {}\n", this->args_info->file_arg);
    
        premGeneralLifeCycle();

    }
    else if (this->args_info->install_arg)
    {
       fmt::print("Install new dict {}\n", this->args_info->install_arg);
    }
    else if (this->args_info->remove_arg)
    {
       fmt::print("Remove dict {}\n", this->args_info->remove_arg);
    }

}
