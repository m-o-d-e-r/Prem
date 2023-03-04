
#include "core/config_reader.h"

#include "core/args_preprocessor.h"
#include "core/args_router.h"

#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)



int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");


    ConfigReader config; // read config and check config path

    ArgsPreprocessor __args_preprocessor; // get arguments from a command line
    __args_preprocessor.parse(argc, argv);
//    __args_preprocessor.__show_args_map();

    ArgsRouter __args_router(__args_preprocessor.getArgsInfo(), &config); // run different parts of program
    __args_router.run();


    return 0;

}
