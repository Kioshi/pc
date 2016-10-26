// fssim.cpp : Defines the entry point for the console application.
//
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

enum eType
{
    FIL = 0,
    DIR
};

std::deque<std::string> toVector(std::string string)
{
    std::string s;
    std::deque<std::string> words;
    for (int i = 0; i < string.length(); i++)
    {
        s += string[i];
        if (string[i] == '/')
        {
            words.push_back(s);
            s.clear();
        }
    }
    if (!s.empty())
        words.push_back(s);

    return words;
}

class Node
{
public:
    Node(std::string name, Node* parent = nullptr)
    {
        _name = name;
        _parent = parent ? parent : this;
        _typ = (eType)(name[name.length() - 1] == '/');
    }

    void insert(std::deque<std::string> words)
    {
        if (words.empty())
            return;

        for (auto c : childs)
        {
            if (c->_name == words[0])
            {
                words.pop_front();
                c->insert(words);
                return;
            }
        }
        Node* n = new Node(words[0], this);
        childs.push_back(n);
        words.pop_front();
        n->insert(words);
    }

    eType _typ;
    std::string _name;
    Node* _parent;
    std::vector<Node*> childs;


};

Node* load(std::ifstream& in)
{
    Node* root = new Node("/");
    std::string line;
    while (std::getline(in, line))
    {
        std::deque<std::string> words;
        words = toVector(line);

        if (!words.empty() && words[0] == "/")
            words.pop_front();

        root->insert(words);
    }

    return root;
}

bool isDir(Node * node)
{
    return node->_name[node->_name.length() - 1] == '/';
}

Node* root;
Node * current;

Node * findNode(Node * curr, std::deque<std::string>& words, bool onlyDir = true)
{
    if (words.empty())
        return curr;

    if (onlyDir && !isDir(curr))
        return curr;

    std::string currString = words[0];
    words.pop_front();
    while (currString == "./" || currString == ".")
    {
        if (words.empty())
            return curr;

        currString = words[0];
        words.pop_front();
    }

    if (currString == "../" || currString == "..")
        return findNode(curr->_parent, words);

    for (Node* c : curr->childs)
    {
        if (c->_name == currString || c->_name == (currString+"/"))
            return findNode(c, words);
    }

    return nullptr;
    

}

Node* cd(std::string path)
{
    std::deque<std::string> words = toVector(path);
    if (path[0] == '/')
    {
        words.pop_front();
        return findNode(root, words);
    }
    else
    {
        return findNode(current, words);
    }
}

std::string pwd(Node* curr)
{
    std::string s;
    if (curr->_parent && curr->_parent != curr)
        s = pwd(curr->_parent);
    s += curr->_name;

    return s;
}

void ls(Node* curr)
{
    std::string s;
    for (auto n : curr->childs)
        std::cout << pwd(curr) << n->_name << std::endl;
}

bool checkName(std::string name, std::string search)
{
    for (int i = 0; i < search.length(); )
    {
        if (name[i] == search[i])
        {
            i++;
            continue;
        }
        else if (search[i] == '*')
        {
            for (int j = i + 1; j < name.length(); j++)
                if (checkName(name.c_str() + j, search.c_str() + i + 1))
                    return true;
            return false;
        }
        else
            return false;
    }
    return true;
}

void find(Node* curr, std::string search)
{
    if (!isDir(curr) && checkName(curr->_name, search))
        std::cout << pwd(curr) << std::endl;
    for (auto n : curr->childs)
        find(n, search);
}

int main()
{
    std::ifstream myfile("fs.txt");
    if (myfile.is_open())
    {
        root = load(myfile);
        current = root;
        myfile.close();
    }
    else
        return 1;

    std::string line;
    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        std::string command;
        std::string firstArg;
        std::string secondArg;
        ss >> command >> firstArg >> secondArg;

        Node * first = nullptr;
        Node * second = nullptr;
        if (!firstArg.empty())
            first = cd(firstArg);
        if (!secondArg.empty())
            second = cd(secondArg);
        
        std::cout << "$" << command;
        if (!firstArg.empty())
            std::cout << " " << firstArg;
        if (!secondArg.empty())
            std::cout << " " << secondArg;
        std::cout << std::endl;

        if (command == "cd")
        {
            if (firstArg.empty())
            {
                std::cout << "ERROR not enough arguments" << std::endl;
                continue;
            }
            if (!first)
                std::cout << "ERROR path does not exist" << std::endl;
            else if (!isDir(first))
                std::cout << "ERROR target is not a directory" << std::endl;
            else
                current = first;
        }
        else if (command == "ls")
        {
            if (!firstArg.empty())
            {
                if (!first)
                {
                    std::cout << "ERROR path does not exist" << std::endl;
                    continue;
                }
            }
            else
                first = current;

            ls(first);
        }
        else if (command == "mv")
        {
            if (firstArg.empty())
            {
                std::cout << "ERROR not enough arguments" << std::endl;
                continue;
            }
            
            if (!second)
                second = current;
            if (!first)
            {
                std::cout << "ERROR source file not found" << std::endl;
                continue;
            }
            else if (isDir(first))
            {
                std::cout << "ERROR source is directory" << std::endl;
                continue;
            }

            std::vector<Node*>::iterator itr;
            for (itr = second->childs.begin(); itr != second->childs.end(); ++itr)
                if ((*itr)->_name == first->_name)
                    break;
            if (itr != second->childs.end())
            {
                second->childs.erase(itr);
                delete *itr;
            }
            second->childs.push_back(first);
            first->_parent->childs.erase(std::find(first->_parent->childs.begin(), first->_parent->childs.end(), first));
            first->_parent = second;
        }
        else if (command == "cp")
        {
            if (firstArg.empty())
            {
                std::cout << "ERROR not enough arguments" << std::endl;
                continue;
            }
            
            if (!second)
                second = current;
            if (!first)
            {
                std::cout << "ERROR source file not found" << std::endl;
                continue;
            }
            else if (isDir(first))
            {
                std::cout << "ERROR source is directory" << std::endl;
                continue;
            }

            std::vector<Node*>::iterator itr;
            for (itr = second->childs.begin(); itr != second->childs.end(); ++itr)
                if ((*itr)->_name == first->_name)
                    break;
            if (itr != second->childs.end())
            {
                second->childs.erase(itr);
                delete *itr;
            }

            second->childs.push_back(new Node(first->_name,second));
        }
        else if (command == "find")
        {
            if (firstArg.empty())
            {
                std::cout << "ERROR not enough arguments" << std::endl;
                continue;
            }

            if (!secondArg.empty() && !second)
            {
                std::cout << "ERROR path does not exist" << std::endl;
                continue;
            }
            else if (!second)
                second = current;

            find(second, firstArg);
        }
        else if (command == "pwd")
        {
            std::cout << pwd(current) << std::endl;
        }
        else
            std::cout << "ERROR unknown command." << std::endl;
    }

    return 0;
}

