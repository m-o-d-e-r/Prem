
#include <fstream>

#include "dict_reader.h"



DictReader::DictReader(__PremPath path)
{
    __path_to_dict = path;
    __data = new __DictData;

}


DictReader::~DictReader()
{
    if (__data)
        delete __data;

}


void DictReader::read_dict()
{
    __PremPath content_path = __path_to_dict / "content.pdict";

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


__PremPath DictReader::get_dict_path() {return __path_to_dict;}


__DictData* DictReader::get_dict_data() {return __data;}
