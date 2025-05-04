/*
* Full name: Mike Luu
* Student ID: 2451334
* Chapman email: duluu@chapman.edu
* Course: CPSC 350 - 04
* Assignment: Programming Assignment 5
*/

#include "RunScareGame.h"
#include "TournamentTree.h"  // Forward declaration is sufficient
#include <fstream>
#include <iostream>

RunScareGame::RunScareGame(const std::string& input, bool isDouble)
    : inputFile(input), isDoubleElimination(isDouble) {
    // Set output file name (replace .txt with .dot)
    outputFile = inputFile.substr(0, inputFile.find_last_of('.')) + ".dot";
    loadMonsters();
}

RunScareGame::~RunScareGame() {
    // Clean up monster objects
    for (Monster* monster : monsters) {
        delete monster;
    }
}

void RunScareGame::loadMonsters() {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        // Remove trailing period if present
        if (!line.empty() && line.back() == '.') {
            line.pop_back();
        }

        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string name = line.substr(0, commaPos);
            std::string powerStr = line.substr(commaPos + 1);

            // Trim whitespace
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
            powerStr.erase(0, powerStr.find_first_not_of(" \t"));
            powerStr.erase(powerStr.find_last_not_of(" \t") + 1);

            try {
                int power = std::stoi(powerStr);
                monsters.push_back(new Monster(name, power));
            } catch (const std::exception& e) {
                std::cerr << "Error parsing power level for monster: " << name << std::endl;
            }
        }
    }

    file.close();
}

void RunScareGame::runTournament() {
    TournamentTree<Monster> tournament;

    if (isDoubleElimination) {
        tournament.runDoubleElimination(monsters);
    } else {
        tournament.runSingleElimination(monsters);
    }

    tournament.saveTreeAsDot(outputFile);

    // Print tournament champion
    Monster* champion = tournament.getChampion();
    if (champion) {
        std::cout << "Champion: " << champion->name
                  << " (Power: " << champion->screamPowerLevel << ")" << std::endl;
    }
}
