
#ifndef _TRIE_H_
#define _TRIE_H_

#include <vector>
#include <string>
#include <memory>


//#define DEBUG_TRIE_MODULES

#ifdef DEBUG_TRIE_MODULES
    #include <iostream>

    #define __DEBUG_CALL_CONSTRUCTOR(v) std::cout << "  Constructor\t" << v << std::endl
    #define __DEBUG_CALL_DESTRUCTOR(v) std::cout << "  Destructor\t" << v << std::endl

#else
    #define __DEBUG_CALL_CONSTRUCTOR(v) (void)(v)
    #define __DEBUG_CALL_DESTRUCTOR(v) (void)(v)

#endif


class TrieNode;
#define __TrieNode_Ptr std::shared_ptr<TrieNode>
#define __make_TrieNode_Ptr std::make_shared
#define __FondedWords std::vector<std::string>



class TrieNode
{
private:
    std::vector<__TrieNode_Ptr> __childs;
    bool __visited     = false;
    char __value       = '$';
    bool __end_of_word = false;

public:
    TrieNode();
    TrieNode(char value, bool is_eow);
    ~TrieNode();

    void setValue(char value);
    char getValue();

    bool isVisited();
    void makeVisited();

    bool isEndOfWord();

    void addChild(__TrieNode_Ptr child);
    std::vector<__TrieNode_Ptr>& getChilds();

};



class CommandTrie
{
private:
    __TrieNode_Ptr __root;
    std::string __current_word;

public:
    CommandTrie();
    ~CommandTrie();

    void insert(std::string str);

    __FondedWords* find(std::string str);

};


#endif
