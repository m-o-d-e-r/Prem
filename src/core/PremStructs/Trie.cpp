
#include <stack>
#include <iostream>

#include "Trie.h"


TrieNode::TrieNode() {__DEBUG_CALL_CONSTRUCTOR(__value);}


TrieNode::TrieNode(char value, bool is_eow)
{
    __value       = value;
    __end_of_word = is_eow;
    __DEBUG_CALL_CONSTRUCTOR(value);
}


TrieNode::~TrieNode() {__DEBUG_CALL_DESTRUCTOR(__value);}


void TrieNode::setValue(char value) {__value = value;}


char TrieNode::getValue() {return __value;}


bool TrieNode::isVisited() {return __visited;}


void TrieNode::makeVisited() {__visited = true;}


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


__FondedWords* CommandTrie::find(std::string str)
{
    __FondedWords* fonded_strings_data = new __FondedWords;
    std::stack<__TrieNode_Ptr> node_stack;
    node_stack.push(__root);

    int char_position = 0;
    std::string word;


    while (!node_stack.empty())
    {
        __TrieNode_Ptr current_node = node_stack.top();

        if (!current_node->isVisited())
        {
            word += current_node->getValue();
        }


        if (current_node->getChilds().size() > 0)
        {
            int n_count = 0;
            for (auto item : current_node->getChilds())
            {
                if (!item->isVisited())
                {
                    node_stack.push(item);
                }
                else
                    n_count++;
            }

            if (n_count == current_node->getChilds().size())
            {
                current_node->makeVisited();
                node_stack.pop();
                word.erase(word.length() - 1);
            }

        } else {
            fonded_strings_data->push_back(word);
//            std::cout << word << "\n";

            node_stack.pop();
            word.erase(word.length() - 1);
        }

        current_node->makeVisited();

    }


    return fonded_strings_data;

}
