/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.cpp
 * Author: s134622
 * 
 * Created on 11. februar 2017, 13:06
 */

#include <cstring>
#include <iostream>
#include <algorithm>
#include <memory>
#include <thread>

#include "Board.h"
#include "ThreadPool.h"


#define index(lettter) (lettter->x + (lettter->y * width))


/**
 * The function parses all the nodes of the board and assignees the neighbors 
 * for each one of the letters
 * 
 * @param brd Used to specify the board.
 * @param width Used to specify the width of the board.
 * @param height Used to specify the height of the board.
 */
static void InitNeighbours(std::vector<std::unique_ptr<Letter>>&brd,
                           unsigned width,
                           unsigned height)
{
    unsigned xStart, yStart;
    long unsigned xStop, yStop;
    for(size_t i = 0; i < brd.size(); i++)
    {
        xStart = brd[i]->x - 1;

        if(xStart > brd[i]->x)//overflow
        {
            xStart = 0;
        }
        xStop = brd[i]->x + 1;
        if(xStop == width)
        {
            xStop = width - 1;
        }
        yStart = brd[i]->y - 1;
        if(yStart > brd[i]->y)//overflow
        {
            yStart = 0;
        }
        yStop = brd[i]->y + 1;
        if(yStop == height)
        {
            yStop = height - 1;
        }

        for(unsigned k = xStart; k <= xStop; k++)
        {
            for(unsigned j = yStart; j <= yStop; j++)
            {
                if(k == brd[i]->x && j == brd[i]->y)
                {
                    continue;
                }
                brd[i]->neighbours.push_back(brd[k + j * width].get());
            }
        }
    }
}


Board::Board(const char* board, unsigned width, unsigned height):
    width{width},
height{height}
{
    size_t len = width* height;
    for(size_t i = 0; i < len; i++)
    {
        brd.push_back(std::move(std::make_unique<Letter>(board[i], i / width, i % width)));
    }

    InitNeighbours(brd, width, height);

}


/** 
 * @param start Used to specify the word.
 * @return Return the score for a specific word;
 */
static inline size_t ScoreWord(size_t wordLength)
{
    // the dictionary doesn't include words smaller than 3 so it should not be 
    // possible to get a length smaller than 3
    switch(wordLength)
    {
        case 3:
        case 4:
            return 1;
        case 5:
            return 2;
        case 6:
            return 3;
        case 7:
            return 5;
        default:
            return 11;
    }
}


//                0  1  2  3  4  5  6  7   8   9  10  11  12  13  14  15  16
size_t score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11, 11, 11, 11, 11, 11, 11, 11, 11,
                  11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11};


void Board::AddWord(const std::vector<Letter*>& start, Result& res)
{
    add_lock.lock();
    if(found.SearchWord(start) == Trie::TrieResult::NOT_FOUND)
    {
        res.score += score[start.size()];
        res.words.push_back(start);
        found.AddWord(start);
    }
    add_lock.unlock();
}


void Board::FindWords(std::vector<Letter*> start,
                      const Trie& dict,
                      Result& solution,
                      bool* visited)
{
    Trie::TrieResult res = dict.SearchWord(start);
    switch(res)
    {
        case Trie::TrieResult::WORD_FOUND:
            AddWord(start, solution);
        case Trie::TrieResult::PREFIX_FOUND:
            for(auto n: start.back()->neighbours)
            {
                if(visited[index(n)])
                {
                    continue;
                }
                visited[index(n)] = true;
                start.push_back(n);
                FindWords(start, dict, solution, visited);
                visited[index(n)] = false;
                start.pop_back();
            }
        default:
            return;
    }
}


Result Board::Solve(const Trie& dict)
{
    Result res;
    ThreadPool tp{std::thread::hardware_concurrency()};
    size_t len = brd.size();
    std::vector< std::future<void> > results;

    for(size_t i = 0; i < len; ++i)
    {
        results.push_back(tp.enqueue([this, &dict, &res, i]
        {
            auto visited = std::make_unique<bool[]>(width*height);
            std::vector<Letter*> word;

            word.push_back(brd[i].get());
            visited[index(brd[i].get())] = true;
            FindWords(word, dict, res, visited.get());
            word.pop_back();
            visited[index(brd[i].get())] = false;
        }));
    }
    for(size_t i = 0; i < results.size(); ++i)
    {
        results[i].get();
    }
    return res;
}
