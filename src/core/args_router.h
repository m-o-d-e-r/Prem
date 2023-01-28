
#ifndef _ARGS_ROUTER_H_
#define _ARGS_ROUTER_H_

#include <string>

#include "args_preprocessor.h"
#include "config_reader.h"


class ArgsRouter
{
private:
    ArgsInfo* args_info;
    ConfigReader* _config;

public:
    ArgsRouter() = delete;
    ArgsRouter(ArgsInfo* , ConfigReader* );

    void run();

};



#endif
