
#include <stack>
#include <iostream>
#include <fstream>

#include "Trie.h"



TrieNode::TrieNode() {__DEBUG_CALL_CONSTRUCTOR(__value);}


TrieNode::TrieNode(char value, bool is_eow)
{
    __value       = value;
    __end_of_word = is_eow;
    __DEBUG_CALL_CONSTRUCTOR(value);
}


TrieNode::~TrieNode() {__DEBUG_CALL_DESTRUCTOR(__value);}


char TrieNode::getValue() {return __value;}


bool TrieNode::isEndOfWord() {return __end_of_word;}


void TrieNode::addChild(__TrieNode_Ptr child) {__childs.push_back(child);}


std::vector<__TrieNode_Ptr>& TrieNode::getChilds() {return __childs;}




CommandTrie::CommandTrie()
{
    __root = __make_TrieNode_Ptr<TrieNode>();
}


CommandTrie::~CommandTrie()
{

}


void CommandTrie::insert(std::string str)
{
    __TrieNode_Ptr current_node = __root; // set root as current node
    char current_char;
    bool child_with_value_exist;
    bool is_eow = false;

    while (true)
    {
        if (str.length() == 0)          // exist if length of str is 0
            break;

        if (str.length() == 1)
            is_eow = true;

        current_char = str[0];          // get first char from string
        child_with_value_exist = false;


        for (auto item : current_node->getChilds()) // check if exist node with current char
        {
            if (item->getValue() == current_char)
            {
                current_node = item;
                child_with_value_exist = true;
                break;
            }
        }

        if (!child_with_value_exist)
        {
            __TrieNode_Ptr newChild = __make_TrieNode_Ptr<TrieNode>(current_char, is_eow);
            current_node->addChild(newChild);
            current_node = newChild;
        }

        str.erase(0, 1);
    }

}


__TrieData& CommandTrie::find(std::string str)
{
    if (!str.length())
        return __data;

    __data.clear();

    __TrieNodePair node_pair = __get_last_valid_node(str);
    __TrieNode_Ptr last_valid_node = std::get<0>(node_pair);

    if (!last_valid_node)
        return __data;


    for (int i = 0; i < std::get<1>(node_pair) - 1; i++)
    {
        __prefix += str[i];
    }

    __build_trie_data(last_valid_node);

    __prefix = "";
    return __data;
}


__TrieNodePair CommandTrie::__get_last_valid_node(std::string str)
{
    __TrieNode_Ptr current_node = __root;
    char current_char;
    bool exist;
    int index = 0;


    while (true)
    {
        if (!current_node->getChilds().size())
            return {nullptr, 0};

        current_char = str[0];
        exist = false;


        for (auto item : current_node->getChilds())
        {
            if (item->getValue() == current_char)
            {
                current_node = item;
                exist = true;
                break;
            }
        }

        if (!exist)
            break;

        str.erase(0, 1);
        index++;
    }

    if (current_node->getValue() == '$')
        return {nullptr, 0};

    return {current_node, index};

}


void CommandTrie::__build_trie_data(__TrieNode_Ptr& node)
{
    for (auto item : node->getChilds())
    {
        __current_word += node->getValue();
        __build_trie_data(item);
        __current_word.erase(__current_word.length() - 1);
    }

    if (node->isEndOfWord())
    {
        __data.push_back(__prefix + __current_word + node->getValue());
    }

}
