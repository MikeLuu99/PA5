// main.cpp
#include <iostream>
#include <string>
#include "RunScareGame.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt> <single|double>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string tournamentType = argv[2];

    bool isDouble = (tournamentType == "double");

    // Create and run the tournament
    RunScareGame game(inputFile, isDouble);
    game.runTournament();

    return 0;
}
