
#include <string>

#include "cmdline.h"





class ArgsRouter
{
private:
    gengetopt_args_info* args_info;

public:
    ArgsRouter() = delete;
    ArgsRouter(gengetopt_args_info* );

    void run();

};
