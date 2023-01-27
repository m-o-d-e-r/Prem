
#ifndef _CONFIG_READER_H_
#define _CONFIG_READER_H_

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


#endif
