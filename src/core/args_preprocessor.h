
#include <map>
#include <string>


class ArgsPreprocessor
{
private:
    std::map<std::string, std::string> __args_map;

    int argc;
    char** argv;

public:
    ArgsPreprocessor();
    ArgsPreprocessor(int, char**);

    int parse();
    void __show_args_map();

};

