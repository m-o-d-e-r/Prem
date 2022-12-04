#include <iostream>
#include <vector>
#include <string>


class TrieNode
{
private:
    char value = '$';
    std::vector<TrieNode*> childs;

public:
    TrieNode() {}
    TrieNode(char value) {this->value = value;}
    ~TrieNode() {}

    void setValue(char value) {this->value = value;}
    char getValue() {return this->value;}

    void addChild(TrieNode* child) {this->childs.push_back(child);}
    std::vector<TrieNode*> getChilds() {return this->childs;}

};



class CommandTrie
{
private:
    TrieNode* root;

public:
    CommandTrie() {root = new TrieNode;}
    ~CommandTrie() {}

    void insert(std::string str)
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
    bool isExist(std::string str)
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
    TrieNode* __getLastChild(std::string str)
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

    void __getSimple(std::string str, TrieNode* node, std::vector<std::string>* lst)
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
    std::vector<std::string>* getSimple(std::string str)
    {
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

};



int main()
{
    CommandTrie trie;
    trie.insert("Hello man");
    trie.insert("Hello nigga");
    trie.insert("Hehe");
    trie.insert("Himama");
    trie.insert("Himars");
    trie.insert("world");

    for (auto i : *trie.getSimple("Hehe"))
    {
        std::cout << i << "\n";
    }
}
