/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: s134622
 *
 * Created on 11. februar 2017, 17:05
 */

#ifndef NODE_H
#define NODE_H

#include <array>
#include <memory>
#include "Letter.h"

constexpr char alphabet = 26;

/**
 * The class is used to specify the base element of the Trie structure
 */
class Node {
public:
    Node() : val{' '}, isWord{false}, children{nullptr}
    {
    }
    Node(char c) : val{c}, isWord{false}, children{nullptr}
    {
    }

    /**
     * Represents the letter of the node.
     */
    char val;
    /**
     * If the character is the last letter of a word this will be set to true.
     */
    bool isWord;

    /**
     * 
     * @param c Used to specify the child.
     * @return Returns the child if found else nullptr.
     */
    Node* findChild(char c) {
        return children[c - 'a'].get();
    }

    /**
     * 
     * @param child Used to specify the child that needs to be appended.
     */
    void appendChild(std::unique_ptr<Node> child) {
        children[child->val - 'a'] = std::move(child);
    }

private:
    std::array<std::unique_ptr<Node>, alphabet> children;
};

#endif /* NODE_H */

