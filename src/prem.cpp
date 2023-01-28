
#include <string>
#include <iostream>

#include <ncurses.h>

#include "interface/BaseWindow.h"
#include "interface/BufferedWindow.h"


#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)

#include "core/PremStructs/BufferItem.h"

#include "core/args_preprocessor.h"
//#include "core/args_router.h"

//#include "core/config_reader.h"


#include <getopt.h>




int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");


//    ConfigReader config;

    ArgsPreprocessor __args_preprocessor;
    __args_preprocessor.parse(argc, argv);


    /*ArgsRouter __args_router(__args_preprocessor.getArgsTable());
    __args_router.run();*/


    return 0;
}
