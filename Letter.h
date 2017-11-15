/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Letter.h
 * Author: s134622
 *
 * Created on 11. februar 2017, 13:02
 */

#ifndef LETTER_H
#define LETTER_H

#include <string>
#include <array>
#include <memory>

/**
 * The class represents the base node for the Boggle board.
 */
class Letter {
public:

    /**
     * 
     * @param value Used to specify the value of the letter.
     * @param x Used to specify the column position of the letter.
     * @param y Used to specify the row position of the letter
     */
    Letter(char value, unsigned y, unsigned x) :
    val{value},
    x{x},
    y{y}
    {
        neighbours.fill(nullptr);
    }
    Letter() :
    val{' '},
    x{0},
    y{0}
    {
        neighbours.fill(nullptr);
    }

    //    std::string ToString() {
    //        std::string str{std::string(1, val) + "[" + std::to_string(x) + ":" + std::to_string(y) + "]"};
    //        for (int i = 0; neighbours[i]!=nullptr; i++) {
    //            str += std::string(1, neighbours[i]->val) + ",";
    //        }
    //        return str;
    //    }

    char val;
    unsigned x;
    unsigned y;
    /**
     * During the backtracking algorithm this is set to true if the letter is 
     * part of a word.
     */
    std::array<Letter*,8> neighbours;
private:

};

#endif /* LETTER_H */

