
#include "config_reader.h"
#include "help_functions.h"



static void __load_toml_file(toml::table& _table, std::filesystem::path _toml_file)
{
    if (_is_file_exist(_toml_file))
    {
        _table = toml::parse_file(_toml_file.c_str());

    } else {
        auto __src = fmt::format(
            "src/.prem.bak/config/{}",
            _toml_file.filename().c_str()
        );

        if (
            _copy_folder(
                std::filesystem::path(__src),
                std::filesystem::path(_toml_file.parent_path())
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
                    "\t[-] error while coping config file [{}] FROM {} TO {}\n",
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
    // FIX: 
    __base_path = __PathObject(_get_user_home_dir()) / ".prem";


    if (_is_folder_exist(__base_path))
    {
        __PathObject config_path = getConfigPath();
        if (_is_folder_exist(config_path))
        {
            __load_toml_file(this->__table["info"], config_path / "info.toml");
            __load_toml_file(this->__table["prem"], config_path /"prem.toml");

        } else {
            print_message("\t[-] prem configuration folder is not exist\n", MessageType::ERROR);
            _copy_folder("src/.prem.bak", __base_path);
            print_message("\t[+] prem configuration folder was created\n", MessageType::COMPLETED);

        }


        __PathObject dict_path = getDictPath();
        if (!_is_folder_exist(dict_path))
        {
            print_message("\t[-] prem dict folder is not exist\n", MessageType::ERROR);
            _copy_folder("src/.prem.bak", __base_path);
            print_message("\t[+] prem dict folder was created\n", MessageType::COMPLETED);

        }

    } else {
        print_message(
            fmt::format(
                "\t[-] prem base folder is not exist\n"
            ).c_str(),
            MessageType::ERROR
        );

        _create_folder(__base_path);
        _copy_folder("src/.prem.bak", __base_path);

        print_message(
            fmt::format(
                "\t[+] prem base folder was created\n"
            ).c_str(),
            MessageType::COMPLETED
        );

    }

}


toml::table& ConfigReader::getTableByName(std::string table_name)
{
    return this->__table[table_name];
}


__PathObject ConfigReader::getBasePath()
{
    return __base_path;
}


__PathObject ConfigReader::getConfigPath()
{
    return __base_path / "config";
}


__PathObject ConfigReader::getDictPath()
{
    return __base_path / "dict";
}

