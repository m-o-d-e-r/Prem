
#ifndef _DICT_READER_H_
#define _DICT_READER_H_

#include <vector>

#include "./help_functions.h"

#define __PremPath std::filesystem::path
#define __DictData std::vector<std::string>



class DictReader
{
private:
    __PremPath __dict_path;
    std::string __dict_name;
    __DictData* __data;

private:
    bool __is_valid_dict(); // TODO: 

public:
    DictReader(__PremPath, std::string);
    ~DictReader();

    void read_dict();

    __PremPath get_dict_path();
    __DictData* get_dict_data();

};



#endif
