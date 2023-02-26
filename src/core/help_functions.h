
#ifndef _HELP_FUNCTIONS_H_
#define _HELP_FUNCTIONS_H_

#include <filesystem>

#include <fmt/format.h>


#define DEBUG

#ifdef DEBUG
    #include <iostream>

    #define __DEBUG_PRINT(x) std::cout << x << std::endl
#endif



enum class MessageType
{
    ERROR = -1,
    NOTIFICATION,
    COMPLETED

};





bool _is_folder_exist(char*);

bool _is_file_exist(char*);
bool _is_file_exist(const char*);

void _create_folder(char*);
void _create_file(char*);

bool _copy_folder(char*, char*);

char* _get_user_home_dir();

void print_message(char*, MessageType);

void print_message(const char*, MessageType);


#ifdef DEBUG

#include <fstream>

template <typename T>
void __DEBUG_PRINT_TO_FILE(std::string path, T data)
{
    std::fstream out(path, std::ios_base::out | std::ios_base::trunc);
    out << data;
}

#endif



#endif