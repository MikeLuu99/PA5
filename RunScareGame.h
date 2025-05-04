/*
* Full name: Mike Luu
* Student ID: 2451334
* Chapman email: duluu@chapman.edu
* Course: CPSC 350 - 04
* Assignment: Programming Assignment 5
*/

#ifndef RUN_SCARE_GAME_H
#define RUN_SCARE_GAME_H

#include <string>
#include <vector>
#include "Monster.h"

class RunScareGame {
private:
    std::string inputFile;
    std::string outputFile;
    bool isDoubleElimination;
    std::vector<Monster*> monsters;

    void loadMonsters(); // Parses input file and loads monsters

public:
    RunScareGame(const std::string& input, bool isDouble);
    ~RunScareGame();

    void runTournament();
};

#endif
