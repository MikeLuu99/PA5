#include "RunScareGame.h"
#include <fstream>
#include <iostream>
#include <sstream>

RunScareGame::RunScareGame(const std::string& filename, bool isDouble) 
    : inputFilename(filename), isDoubleElimination(isDouble), tournament(nullptr) {
    monsters = readMonstersFromFile(filename);
}

RunScareGame::~RunScareGame() {
    delete tournament;
    for (auto monster : monsters) {
        delete monster;
    }
}

std::vector<Monster<int>*> RunScareGame::readMonstersFromFile(const std::string& filename) {
    std::vector<Monster<int>*> monsters;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return monsters;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int power;
        
        if (iss >> name >> power) {
            monsters.push_back(new Monster<int>(name, power));
        }
    }
    
    file.close();
    return monsters;
}

void RunScareGame::runTournament() {
    if (monsters.empty()) {
        std::cerr << "No monsters loaded from file!" << std::endl;
        return;
    }
    
    tournament = new TournamentTree<int>(monsters);
    
    if (isDoubleElimination) {
        tournament->doubleElimination();
        tournament->saveTreeAsDot("double_elimination_tournament.dot");
    } else {
        tournament->singleElimination();
        tournament->saveTreeAsDot("single_elimination_tournament.dot");
    }
}