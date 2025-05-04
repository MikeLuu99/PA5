/*
* Full name: Mike Luu
* Full name: Lance Nguyen
* Student ID: 2451334
* Chapman email: duluu@chapman.edu lannguyen@chapman.edu
* Course: CPSC 350 - 04 CPSC 350 - 01
* Assignment: Programming Assignment 5
*/

#ifndef RUN_SCARE_GAME_H
#define RUN_SCARE_GAME_H

#include <string>
#include <vector>
#include "Monster.h"

// RunScareGame manages the tournament operations including loading monsters and running matches
class RunScareGame {
private:
    std::string inputFile;           // Path to file containing monster data
    std::string outputFile;          // Path where tournament tree will be saved
    bool isDoubleElimination;        // Tournament type flag: true for double elimination
    std::vector<Monster*> monsters;  // Collection of all monsters in tournament

    void loadMonsters();             // Reads and parses monster data from input file

public:
    // Constructor: Initializes game with input file path and tournament type
    RunScareGame(const std::string& input, bool isDouble);
    
    // Destructor: Cleans up dynamically allocated monsters
    ~RunScareGame();

    // Executes the tournament based on specified elimination type
    void runTournament();
};

#endif
