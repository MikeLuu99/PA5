#ifndef RUNSCAREGAME_H
#define RUNSCAREGAME_H

#include <string>
#include <vector>
#include "Monster.h"
#include "TournamentTree.h"

class RunScareGame {
public:
    RunScareGame(const std::string& filename, bool isDouble = false);
    ~RunScareGame();
    void runTournament();

private:
    std::vector<Monster<int>*> readMonstersFromFile(const std::string& filename);
    std::string inputFilename;
    bool isDoubleElimination;
    std::vector<Monster<int>*> monsters;
    TournamentTree<int>* tournament;
};

#endif