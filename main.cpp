#include <iostream>
#include <string>
#include "RunScareGame.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <single|double>" << std::endl;
        return 1;
    }

    std::string tournamentType = argv[2];
    bool isDouble = (tournamentType == "double");

    RunScareGame game(argv[1], isDouble);
    game.runTournament();

    return 0;
}