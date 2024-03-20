
#include <string>
#include <tuple>
#include <map>


typedef std::tuple<std::string, std::string, bool, bool, std::string> __OptionRule;



class Option
{
private:
    __OptionRule* __rule;

public:
    Option() = delete;
    Option(__OptionRule*);
    ~Option();

    std::string getShort();
    std::string getLong();
    bool getStatus();
    bool isBool();
    std::string getDescription();

};





class ArgsRouter
{
private:
    std::map<std::string, Option*> __args_map;

public:
    ArgsRouter();
    ~ArgsRouter();



};
