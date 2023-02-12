
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
        std::cout << "\n";
    } else {
        std::cout << "Not found\n\n";
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


//    std::cout << std::get<0>(commandStorage.findNodePair("W")) << "\n";
//    std::cout << std::get<0>(commandStorage.findNodePair("Rusd"))->getValue() << "\n";

    print_simple(commandStorage.find("R"));
    print_simple(commandStorage.find("R"));
    /*print_simple(commandStorage.find("Ru"));
    print_simple(commandStorage.find("Rus"));
    print_simple(commandStorage.find("P"));
    print_simple(commandStorage.find("Py"));
    print_simple(commandStorage.find("Pyt"));
    print_simple(commandStorage.find("Pe"));

    print_simple(commandStorage.find("C"));

    print_simple(commandStorage.find("W"));*/

    /*std::cout << std::get<0>(commandStorage.findNodePair("C"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("C"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("C#"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("C#"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("C+"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("C+"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Ru"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Ru"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Rus"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Rus"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Rust"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Rust"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("P"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("P"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Py"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Py"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Pe"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Pe"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Java"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Java"))->getValue() << "\n";
    std::cout << std::get<0>(commandStorage.findNodePair("Java S"))->getValue() << "\t" << std::get<1>(commandStorage.findNodePair("Java S"))->getValue() << "\n";*/


    /*print_simple(commandStorage.getSimple("C"));
    print_simple(commandStorage.getSimple("P"));*/

    /*print_simple(commandStorage.find("Python"));
    print_simple(commandStorage.find("Python"));*/
    
//    commandStorage.find("R");


//    print_simple(commandStorage.getSimple("J"));

    return 0;

}

// g++ -o test src/test.cpp src/core/PremStructs/Trie.cpp
