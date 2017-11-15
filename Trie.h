/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trie.h
 * Author: s134622
 *
 * Created on 11. februar 2017, 17:04
 */

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <memory>
#include <vector>

#include "Node.h"
#include "Letter.h"

/**
 * The class represents a Trie tree and is used to hold a dictionary.
 */
class Trie {
public:

    /**
     * To make the search more efficient there are 3 possible solution for each combination of letters:
     * WORD_FOUND is a word
     * PREFIX_FOUND is the prefix of a word
     * NOT_FOUND there isn't a word that start with this combination of letters
     */
    enum class TrieResult {
        WORD_FOUND, PREFIX_FOUND, NOT_FOUND
    };
    Trie();
    Trie(const std::string& path);
    ~Trie();

    /**
     * Loads a dictionary inside the trie, the dictionary has to be a word per line.
     * 
     * @param path Used to specify the path to the dictionary.
     */
    void Load(const char* path);

    /**
     * 
     * @param word Used to specify the word to be added to the dictionary.
     */
    void AddWord(const std::string& word);
    
    void AddWord(const std::vector<Letter*>& word);

    /**
     * @param word Used to specify the word that needs to be searched.
     * @return Returns the result of the word.
     */
    TrieResult SearchWord(const std::vector<Letter*>& word) const;
private:
    std::unique_ptr<Node> root;
};

#endif /* TRIE_H */

