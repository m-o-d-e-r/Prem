
#include <fstream>

#include "dict_reader.h"



DictReader::DictReader(__PremPath path, std::string dict_name)
{
    __dict_path = path;
    __dict_name = dict_name;
    __data = new __DictData;

}


DictReader::~DictReader()
{
    if (__data)
        delete __data;

}


void DictReader::read_dict()
{
    __PremPath content_path = __dict_path / __dict_name / "content.pdict";

    if (_is_file_exist(content_path.c_str()))
    {
        std::string line;
        std::fstream file(content_path, std::ios_base::in);

        if (file.is_open())
        {
            while (!file.eof())
            {
                std::getline(file, line);
                __data->push_back(line);

            }

        }

    } else {
        // TODO: raise error or show in status bar
    }

}


__PremPath DictReader::get_dict_path() {return __dict_path / __dict_name;}


__DictData* DictReader::get_dict_data() {return __data;}
