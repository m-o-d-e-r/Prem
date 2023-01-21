
#include "config_reader.h"


ConfigReader::ConfigReader()
{
    this->__table["info"] = toml::parse_file("src/config/info.toml");
    this->__table["prem"] = toml::parse_file("src/config/prem.toml");
}


toml::table& ConfigReader::getTableByName(std::string table_name)
{
    return this->__table[table_name];
}
