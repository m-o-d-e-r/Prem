
#ifndef _ARGS_PREPROCESSOR_H_
#define _ARGS_PREPROCESSOR_H_

#include <map>
#include <string>

#include <fmt/printf.h>
#include <fmt/color.h>



struct ArgsInfo
{
    std::map<char, char*> mapValues = {
        {'f', nullptr},
        {'i', nullptr},
        {'r', nullptr},
        {'V', nullptr},
        {'h', nullptr},
        {'g', nullptr}
    };

    std::map<char, uint8_t> mapCounter = {
        {'f', 0},
        {'i', 0},
        {'r', 0},
        {'V', 0},
        {'h', 0},
        {'g', 0}
    };

};





class ArgsPreprocessor
{
private:
    ArgsInfo* args_info;

public:
    ArgsPreprocessor();
    ~ArgsPreprocessor();

    void parse(int argc, char** argv);
    void __show_args_map();

    ArgsInfo* getArgsInfo();

};


#endif
