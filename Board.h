/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.h
 * Author: s134622
 *
 * Created on 11. februar 2017, 13:06
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <mutex>
#include "Letter.h"
#include "Trie.h"

class Result {
public:
    Result() : score{0}
    {
    }
    std::vector<std::vector<Letter*>> words;
    size_t score;
private:

};

/**
 * The class represents the Boggle board solver.
 */
class Board {
public:
    /**
     * 
     * @param board Used to specify the board as an array of chars, now row delimiters.
     * @param width Used to specify the width of the board.
     * @param height Used to specify the height of the board.
     */
    Board(const std::string& board, size_t width, size_t height);

    /**
     * Solves the Boggle game.
     * 
     * @param dict Used to specify the dictionary against which the generated words 
     *              have to be tested.
     * @param res Used to specify the result structure in which the results will be stored.
     */
    Result Solve(const Trie& dict);

    //    std::string ToString(){
    //    std::string str;
    //    for (int i = 0; i < brd.size(); i++)
    //    {
    //        str += brd[i]->ToString() + "   ";
    //        if (i % width == width - 1)
    //        {
    //            str += "\r\n";
    //        }
    //    }
    //    return str;
    //}

private:
    /**
     * Recursive function used to find all the valid words present on the board.
     * 
     * @param start Used to specify the vector in which the word will be composed.
     * @param dict Used to specify the dictionary against which the words are validated.
     * @param solution Used to specify the Result object in which the words are 
     *                      added one by one.
     */
    void FindWords(std::vector<Letter*> start,
            const Trie& dict,
            Result& solution,
            bool* visited);

    /**
     * The function populates the result object based on the supplied word.
     * 
     * @param start Used to specify the word that needs to be added.
     * @param res Used to specify the Result object.
     */
    void AddWord(const std::vector<Letter*>& start, Result& res);

    size_t width, height;
    std::vector<std::unique_ptr<Letter>> brd;
    Trie found;
    std::mutex add_lock;
};

#endif /* BOARD_H */

