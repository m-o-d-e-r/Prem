
#include <iostream>

#include "core/PremStructs/Trie.h"


void test(CommandTrie commandStorage, std::string s)
{
    std::cout << "---- '" << s << "' ----\n";

    __TrieData* data = commandStorage.find(s);
    if (data)
    {
        for (auto item : *data)
        {
            std::cout << item << std::endl;
        }
    } else {
        std::cout << "None" << std::endl;
    }

    std::cout << "\n";

}



int main()
{
    CommandTrie commandStorage;
    commandStorage.insert("allow_anon_ssl");
    commandStorage.insert("anon_mkdir_write_enable");
    commandStorage.insert("anon_other_write_enable");
    commandStorage.insert("anon_upload_enable");
    commandStorage.insert("anon_world_readable_only");
    commandStorage.insert("anonymous_enable");
    commandStorage.insert("ascii_download_enable");
    commandStorage.insert("ascii_upload_enable");
    commandStorage.insert("async_abor_enable");

    test(commandStorage, "a");
    test(commandStorage, "an");
    test(commandStorage, "ano");
    test(commandStorage, "anon");
    test(commandStorage, "anon_");
    test(commandStorage, "");
    test(commandStorage, " ");
    test(commandStorage, "$");
    test(commandStorage, "q");
    test(commandStorage, "qwqw");

    return 0;

}

// g++ -o test src/test.cpp src/core/PremStructs/Trie.cpp
