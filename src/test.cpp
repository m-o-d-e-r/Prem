
#include <iostream>

#include "core/PremStructs/Trie.h"



void print_simple(__FondedWords* data)
{
    if (data)
    {
        for (auto item : *data)
        {
            std::cout << item << "\n";
        }

    }

}



int main()
{

    CommandTrie commandStorage;
    commandStorage.insert("Python");
    commandStorage.insert("C++");
    commandStorage.insert("Java");
    commandStorage.insert("C#");
    commandStorage.insert("Java Script");
    commandStorage.insert("C");
    commandStorage.insert("Rust");
    commandStorage.insert("Ruby");
    commandStorage.insert("Perl");


    /*print_simple(commandStorage.getSimple("C"));
    print_simple(commandStorage.getSimple("P"));*/

    print_simple(commandStorage.find("R"));
//    commandStorage.find("R");


//    print_simple(commandStorage.getSimple("J"));

    return 0;

}
