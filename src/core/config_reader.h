
#include <string>
#include <map>

#include "../libs/tomlplusplus/toml.h"



class ConfigReader
{
private:
    std::map<std::string, toml::table> __table;

public:
    ConfigReader();

    toml::table& getTableByName(std::string);

};
