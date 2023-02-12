
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


void TrieNode::makeVisited(bool status) {__visited = status;}


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
    __TrieNodePair node_pair    = findNodePair(str);
    __TrieNode_Ptr parent_node  = std::get<0>(node_pair);
    __TrieNode_Ptr current_node = std::get<1>(node_pair);
    std::string prefix          = std::get<2>(node_pair);


    if (!parent_node)
        return nullptr;


    __FondedWords* fonded_strings_data = new __FondedWords;

    std::stack<__TrieNode_Ptr> node_stack;
    node_stack.push(current_node);

    std::string word;


    while (!node_stack.empty())
    {
        __TrieNode_Ptr top_stack_node = node_stack.top();

        if (!top_stack_node->isVisited())
        {
            word += top_stack_node->getValue();
        }


        if (top_stack_node->getChilds().size() > 0)
        {
            int n_count = 0;
            for (auto item : top_stack_node->getChilds())
            {
                if (!item->isVisited())
                {
                    node_stack.push(item);
                }
                else
                    n_count++;
            }

            if (n_count == top_stack_node->getChilds().size())
            {
                top_stack_node->makeVisited();
                node_stack.pop();
                word.erase(word.length() - 1);
            }

        } else {
            fonded_strings_data->push_back(prefix + word);

            node_stack.pop();
            word.erase(word.length() - 1);
        }

        top_stack_node->makeVisited();

    }

    __setUnvisited(parent_node);


    return fonded_strings_data;

}


__TrieNodePair CommandTrie::findNodePair(std::string str)
{
    std::stack<__TrieNode_Ptr> node_stack;
    node_stack.push(__root);

    int char_index = 0;
    std::string prefix;

    __TrieNode_Ptr parent_node = nullptr;
    __TrieNode_Ptr current_node;
    while (!node_stack.empty())
    {
        current_node = node_stack.top();
        node_stack.pop();

        if (current_node->getChilds().size() > 0)
        {
            int counter = 0;

            for (auto item : current_node->getChilds())
            {
                if (item->getValue() == str[char_index])
                {
                    if (!parent_node)
                    {
                        parent_node = item;
                    }

                    prefix += item->getValue();
                    node_stack.push(item);
                    char_index++;

                }

            }

        }

    }

    if (prefix.length() > 0)
        prefix.erase(prefix.length() - 1);
    return {parent_node, current_node, prefix};

}


void CommandTrie::__setUnvisited(__TrieNode_Ptr start)
{
    std::stack<__TrieNode_Ptr> node_stack;
    node_stack.push(start);


    while (!node_stack.empty())
    {
        __TrieNode_Ptr current_node = node_stack.top();
        node_stack.pop();

        if (current_node->isVisited())
        {
            current_node->makeVisited(false);
        }

//        std::cout << current_node->getValue() << "\n";

        if (current_node->getChilds().size() > 0)
        {
            for (auto item : current_node->getChilds())
            {
                node_stack.push(item);
                if (item->isVisited())
                {
                    item->makeVisited(false);
                }

            }

        }

    }

}
