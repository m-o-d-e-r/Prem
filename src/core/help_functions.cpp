
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <map>

#include <fmt/printf.h>
#include <fmt/color.h>

#include "help_functions.h"



static std::map<MessageType, fmt::color> __MESSAGE_COLOR = {
    {MessageType::ERROR, fmt::color::orange_red},
    {MessageType::NOTIFICATION, fmt::color::dark_cyan},
    {MessageType::COMPLETED, fmt::color::lime_green}
};



bool _is_folder_exist(char* _path_to_folder)
{
    return std::filesystem::is_directory(_path_to_folder);
}


bool _is_folder_exist(std::filesystem::path _path_to_folder)
{
    return std::filesystem::is_directory(_path_to_folder);
}


bool _is_file_exist(char* _path_to_file)
{
    return std::filesystem::exists(_path_to_file);
}


bool _is_file_exist(const char* _path_to_file)
{
    return _is_file_exist(const_cast<char*>(_path_to_file));
}


bool _is_file_exist(std::filesystem::path _path_to_file)
{
    return _is_file_exist(_path_to_file.c_str());
}


void _create_folder(char* _path_to_folder)
{
    if (!_is_folder_exist(_path_to_folder))
        std::filesystem::create_directory(_path_to_folder);
}


void _create_folder(std::filesystem::path _path_to_folder)
{
    if (!_is_folder_exist(_path_to_folder))
        std::filesystem::create_directory(_path_to_folder);
}


void _create_file(char* _path_to_file)
{
    if (!_is_file_exist(_path_to_file))
    {
        std::fstream _out(_path_to_file, std::ios_base::out);
        _out.close();
    }
}


bool _copy_folder(char* _src, char* _dst)
{
    namespace fs = std::filesystem;
    
    fs::path src(_src);
    fs::path dst(_dst);

    return _copy_folder(src, dst);

}


bool _copy_folder(std::filesystem::path _src, std::filesystem::path _dst)
{
    namespace fs = std::filesystem;

    try
    {
        fs::copy(
            _src,
            _dst,
            fs::copy_options::update_existing
            | fs::copy_options::recursive
        );
        return true;
    }
    catch (std::exception& e)
    {
        return false;
    }

}


char* _get_user_home_dir()
{
    return getpwuid(getuid())->pw_dir;
}


void print_message(char* _text, MessageType _type)
{
    fmt::print(
        fg(__MESSAGE_COLOR[_type]),
        _text        
    );

}


void print_message(const char* _text, MessageType _type)
{
    fmt::print(
        fg(__MESSAGE_COLOR[_type]),
        _text        
    );

}
