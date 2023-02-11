
#ifndef _TRIE_H_
#define _TRIE_H_

#include <vector>
#include <string>



class TrieNode
{
private:
    char value = '$';
    std::vector<TrieNode*> childs;

public:
    TrieNode();
    TrieNode(char value);
    ~TrieNode();

    void setValue(char value);
    char getValue();

    void addChild(TrieNode* child);
    std::vector<TrieNode*> getChilds();

};


class CommandTrie
{
private:
    TrieNode* root;
    std::string __current_word;

public:
    CommandTrie();
    ~CommandTrie();

    void insert(std::string str);
    bool isExist(std::string str);

    TrieNode* __getLastChild(std::string str);

    void __getSimple(std::string str, TrieNode* node, std::vector<std::string>* lst);
    std::vector<std::string>* getSimple(std::string str);

};


#endif
