
#include <map>
#include <string>

#include "cmdline.h"


class ArgsPreprocessor
{
private:
    gengetopt_args_info* args_info;

public:
    ArgsPreprocessor();
    ~ArgsPreprocessor();

    void parse(int argc, char** argv);
    void __show_args_map();

    gengetopt_args_info* getArgsTable();

};

