
#ifndef _TRIE_H_
#define _TRIE_H_

#include <vector>
#include <string>
#include <memory>


#define DEBUG_TRIE_MODULES

#ifdef DEBUG_TRIE_MODULES
    #include <iostream>

    #define __DEBUG_CALL_CONSTRUCTOR(v) std::cout << "  Constructor\t" << v << std::endl
    #define __DEBUG_CALL_DESTRUCTOR(v) std::cout << "  Destructor\t" << v << std::endl

#else
    #define __DEBUG_CALL_CONSTRUCTOR(v) (void)(v)
    #define __DEBUG_CALL_DESTRUCTOR(v) (void)(v)

#endif



class TrieNode
{
private:
    char value = '$';
    std::vector<std::shared_ptr<TrieNode>> childs;

public:
    TrieNode();
    TrieNode(char value);
    ~TrieNode();

    void setValue(char value);
    char getValue();

    void addChild(std::shared_ptr<TrieNode> child);
    std::vector<std::shared_ptr<TrieNode>> getChilds();

};


class CommandTrie
{
private:
    std::shared_ptr<TrieNode> root;
    std::string __current_word;

public:
    CommandTrie();
    ~CommandTrie();

    void insert(std::string str);
    bool isExist(std::string str);

    std::shared_ptr<TrieNode> __getLastChild(std::string str);

    void __getSimple(std::string str, std::shared_ptr<TrieNode> node, std::vector<std::string>* lst);
    std::vector<std::string>* getSimple(std::string str);

};


#endif
