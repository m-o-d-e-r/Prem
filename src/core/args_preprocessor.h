
#ifndef _ARGS_PREPROCESSOR_H_
#define _ARGS_PREPROCESSOR_H_

#include <map>
#include <string>



struct ArgsInfo
{
    std::map<std::string, std::string> cmdValues;

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
