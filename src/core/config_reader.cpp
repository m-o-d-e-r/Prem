
#include "config_reader.h"
#include "help_functions.h"



static void __load_toml_file(toml::table& _table, std::filesystem::path _toml_file)
{
    char* _toml_char_path = const_cast<char*>(_toml_file.c_str());

    if (_is_file_exist(_toml_char_path))
    {
        _table = toml::parse_file(_toml_char_path);

        print_message(
            fmt::format(
                "\t[*] config file is loaded: {}\n",
                _toml_char_path
            ).c_str(),
            MessageType::NOTIFICATION
        );

    } else {
        auto __src = fmt::format(
            "src/.prem.bak/config/{}",
            _toml_file.filename().c_str()
        );

        if (
            _copy_folder(
                const_cast<char*>(__src.c_str()),
                const_cast<char*>(_toml_file.parent_path().c_str())
            )
        )
        {
            print_message(
                fmt::format(
                    "\t[+] config file [{}] copied FROM {} TO {}\n",
                    _toml_file.filename().c_str(),
                    __src,
                    _toml_file.c_str()
                ).c_str(),
                MessageType::COMPLETED
            );
        } else {
            print_message(
                fmt::format(
                    "\t[+] error while coping config file [{}] FROM {} TO {}\n",
                    _toml_file.filename().c_str(),
                    __src,
                    _toml_file.c_str()
                ).c_str(),
                MessageType::ERROR
            );

        }

    }

}




ConfigReader::ConfigReader()
{
    /*
    
        TODO: replace some code to PathChecker
    
    */

    char* _home_dir = _get_user_home_dir();
    strcat(_home_dir, "/.prem");


    print_message(
        fmt::format(
            "\t[*] prem base folder: {}\n",
            _home_dir
        ).c_str(),
        MessageType::NOTIFICATION
    );


    if (_is_folder_exist(_home_dir))
    {
        namespace fs = std::filesystem;

        fs::path config_path = fs::path(_home_dir) / "config";

        print_message(
            fmt::format(
                "\t[*] prem base config folder: {}\n\n",
                config_path.c_str()
            ).c_str(),
            MessageType::NOTIFICATION
        );


        if (_is_folder_exist(const_cast<char*>(config_path.c_str())))
        {
            __load_toml_file(this->__table["info"], config_path / "info.toml");
            __load_toml_file(this->__table["prem"], config_path /"prem.toml");

        } else {
            print_message("\t[-] lol, prem configuration folder is not created\n", MessageType::ERROR);
            _copy_folder("src/.prem.bak", _home_dir);
            print_message("\t[+] prem configuration folder was created\n", MessageType::COMPLETED);

        }


    } else {
        print_message(
            fmt::format(
                "\t[-] prem base folder is not exist\n"
            ).c_str(),
            MessageType::ERROR
        );

        _create_folder(_home_dir);

        print_message(
            fmt::format(
                "\t[-] prem base folder was created\n"
            ).c_str(),
            MessageType::COMPLETED
        );

    }

}


toml::table& ConfigReader::getTableByName(std::string table_name)
{
    return this->__table[table_name];
}
