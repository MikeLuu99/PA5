/*
* Full name: Mike Luu
* Full name: Lance Nguyen
* Student ID: 2451334
* Chapman email: duluu@chapman.edu
* Course: CPSC 350 - 04
* Assignment: Programming Assignment 5
*/

#include <string>
#include "RunScareGame.h"

int main(int argc, char* argv[]) {
    std::string inputFile = argv[1];
    std::string tournamentType = argv[2];

    bool isDouble = (tournamentType == "double");

    // Create and run the tournament
    RunScareGame game(inputFile, isDouble);
    game.runTournament();

    return 0;
}
