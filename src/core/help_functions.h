
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

bool _copy_folder(char*, char*);

char* _get_user_home_dir();

void print_message(char*, MessageType);

void print_message(const char*, MessageType);


#endif
