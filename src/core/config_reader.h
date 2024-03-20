
#ifndef _CONFIG_READER_H_
#define _CONFIG_READER_H_

#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "../libs/tomlplusplus/toml.h"

#define __PathObject std::filesystem::path



class ConfigReader
{
private:
    __PathObject __base_path;
    std::map<std::string, toml::table> __table;

public:
    ConfigReader();

    toml::table& getTableByName(std::string);
    __PathObject getBasePath();
    __PathObject getConfigPath();
    __PathObject getDictPath();

};


#endif
