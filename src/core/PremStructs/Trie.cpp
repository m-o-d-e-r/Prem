
#include "Trie.h"


TrieNode::TrieNode() {}
TrieNode::TrieNode(char value) {this->value = value;}
TrieNode::~TrieNode() {}


void TrieNode::setValue(char value) {this->value = value;}
char TrieNode::getValue() {return this->value;}


void TrieNode::addChild(TrieNode* child) {this->childs.push_back(child);}
std::vector<TrieNode*> TrieNode::getChilds() {return this->childs;}



CommandTrie::CommandTrie() {root = new TrieNode;}
CommandTrie::~CommandTrie() {}


void CommandTrie::insert(std::string str)
{
    TrieNode* current_node = this->root;
    char current_char;
    char child_with_value_exist;

    while (true)
    {
        if (str.length() == 0)
            break;

        current_char = str[0];
        child_with_value_exist = false;


        for (auto item : current_node->getChilds())
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
            TrieNode* newChild = new TrieNode(current_char);
            current_node->addChild(newChild);
            current_node = newChild;
        }

        str.erase(0, 1);
    }
}


bool CommandTrie::isExist(std::string str)
{
    TrieNode* current_node = this->root;

    int current_index = 0;
    int cycle_counter = 0;
    while (true)
    {
        for (auto item : current_node->getChilds())
        {
            if (item->getValue() == str[current_index])
            {
                current_node = item;
                current_index++;
                break;
            }
        }

        if (current_index == str.length()) {break;}
        if (cycle_counter == str.length()) {break;}
        cycle_counter++;
    }
    return (current_index == str.length());
}


TrieNode* CommandTrie::__getLastChild(std::string str)
{
    TrieNode* current_node = this->root;

    int current_index = 0;
    while (true)
    {
        for (auto item : current_node->getChilds())
        {
            if (item->getValue() == str[current_index])
            {
//                    std::cout << str[current_index] << "\n";
                current_node = item;
                current_index++;
                break;
            }
        }

        if (current_index == str.length()) {break;}
    }

    return current_node;
}


void CommandTrie::__getSimple(std::string str, TrieNode* node, std::vector<std::string>* lst)
{
    str += node->getValue();

    if (node->getChilds().size() == 0)
    {
        lst->push_back(str);
        return;
    }

    for (auto item : node->getChilds())
    {
        __getSimple(str, item, lst);
    }
}


std::vector<std::string>* CommandTrie::getSimple(std::string str)
{
    __current_word += str;

    std::vector<std::string>* simpleStrings = new std::vector<std::string>;
    TrieNode* current_node = this->__getLastChild(str);

    if (current_node->getChilds().size() == 0)
    {
        simpleStrings->push_back(str);
        return simpleStrings;
    }

    for (auto item : current_node->getChilds())
    {
        this->__getSimple(str, item, simpleStrings);
    }

    return simpleStrings;
}
