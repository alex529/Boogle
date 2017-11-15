/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trie.cpp
 * Author: s134622
 * 
 * Created on 11. februar 2017, 17:05
 */

#include "Trie.h"
#include "Letter.h"


#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>


/**
 * Checks id the file is read properly.
 * @param f Used to specify the file.
 * @return 
 */
static int CheckErrorBits(const std::ifstream& f)
{
    int stop = 0;
    if(f.fail())
    {
        perror("stream failbit (or badbit). error state");
        stop = 1;
    }
    if(f.bad())
    {
        perror("stream badbit. error state");
        stop = 1;
    }
    return stop;
}


/**
 * Used to make a the algorithm more flexible. The better solution would be to 
 * provide the dictionary with "q" instead of "qu" in the first place so no data 
 * parsing would be needed.
 * 
 * @param subject Used to specify the string that needs to be manipulated.
 * @param search Used to specify the search string.
 * @param replace Used to specify the replace string.
 */
static void ReplaceString(std::string& subject, const std::string& search,
                          const std::string& replace)
{
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

Trie::Trie(): root{std::make_unique<Node>()}
{
}


Trie::Trie(const std::string& path): root{std::make_unique<Node>()}
{
    Load(path.c_str());
}


Trie::~Trie()
{
    root.reset();
}


void Trie::Load(const char* path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        perror(path);
    }
    std::string line;
    while(std::getline(file, line))
    {
        if(CheckErrorBits(file))
        {
            break;
        }
        std::transform(line.begin(),
                       line.end(),
                       line.begin(),
                       [](unsigned char c)
                       {
                           return std::tolower(c); });
        ReplaceString(line, "qu", "q");
        AddWord(line);
    }
    file.close();
}


void Trie::AddWord(const std::string& word)
{
    Node* current = root.get();
    for(size_t i = 0; i < word.size(); i++)
    {
        Node* child = current->findChild(word[i]);
        if(child != nullptr)
        {
            current = child;
        }
        else
        {
            std::unique_ptr<Node> tmp = std::make_unique<Node>(word[i]);
            Node* n = tmp.get();
            current->appendChild(std::move(tmp));
            current = n;
        }
    }
    current->isWord = true;
}


void Trie::AddWord(const std::vector<Letter*>& word)
{
    Node* current = root.get();
    for(size_t i = 0; i < word.size(); i++)
    {
        Node* child = current->findChild(word[i]->val);
        if(child != nullptr)
        {
            current = child;
        }
        else
        {
            std::unique_ptr<Node> tmp = std::make_unique<Node>(word[i]->val);
            Node* n = tmp.get();
            current->appendChild(std::move(tmp));
            current = n;
        }
    }
    current->isWord = true;
}


Trie::TrieResult Trie::SearchWord(const std::vector<Letter*>& word) const
{
    Node* current = root.get();

    while(current != nullptr)
    {
        for(size_t i = 0; i < word.size(); i++)
        {
            Node* tmp = current->findChild(word[i]->val);
            if(tmp == nullptr)
                return Trie::TrieResult::NOT_FOUND;
            current = tmp;
        }
        if(current->isWord)
            return Trie::TrieResult::WORD_FOUND;
        else
            return Trie::TrieResult::PREFIX_FOUND;
    }
}