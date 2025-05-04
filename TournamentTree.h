#ifndef TOURNAMENT_TREE_H
#define TOURNAMENT_TREE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "TournamentNode.h"

template <typename T>
class TournamentTree {
private:
    TournamentNode<T>* root;        // Root of the tournament tree
    std::vector<T*> losers;         // Tracks losers for double elimination

    // Helper methods
    TournamentNode<T>* buildSingleEliminationTree(std::vector<T*>& competitors);
    TournamentNode<T>* buildLosersBracket(std::vector<T*>& losers);
    void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) const;

public:
    // Constructor and destructor
    TournamentTree() : root(nullptr) {}
    ~TournamentTree() { delete root; }

    // Tournament methods
    void runSingleElimination(std::vector<T*>& competitors);
    void runDoubleElimination(std::vector<T*>& competitors);
    void saveTreeAsDot(const std::string& filename) const;
    T* getChampion() const { return root ? root->winner : nullptr; }
};

// Implementation of TournamentTree methods
template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(root, file, nodeID);
    file << "}\n";
    file.close();
}

template <typename T>
void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) const {
    if (!node) return;
    int currentID = nodeID++;
    file << " node" << currentID << " [label=\"" << node->winner->name << ", (Power: " << node->winner->screamPowerLevel << ")\"];\n";
    if (node->left) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->left, file, nodeID);
        file << " node" << currentID << " -> node" << leftID << ";\n";
    }
    if (node->right) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->right, file, nodeID);
        file << " node" << currentID << " -> node" << rightID << ";\n";
    }
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::buildSingleEliminationTree(std::vector<T*>& competitors) {
    if (competitors.empty()) return nullptr;

    // Make a copy of competitors to work with
    std::vector<T*> current = competitors;
    std::vector<TournamentNode<T>*> leafNodes;

    // First, create all the leaf nodes (each competitor as its own node)
    for (T* competitor : current) {
        TournamentNode<T>* node = new TournamentNode<T>(competitor);
        leafNodes.push_back(node);
    }

    // Build the tournament tree bottom-up
    while (leafNodes.size() > 1) {
        std::vector<TournamentNode<T>*> nextRound;

        for (size_t i = 0; i < leafNodes.size(); i += 2) {
            if (i + 1 < leafNodes.size()) {
                // Create match between two competitors
                TournamentNode<T>* match = new TournamentNode<T>();
                match->left = leafNodes[i];
                match->right = leafNodes[i + 1];

                // Determine winner based on scream power
                if (*leafNodes[i]->winner > *leafNodes[i + 1]->winner) {
                    match->winner = leafNodes[i]->winner;
                    losers.push_back(leafNodes[i + 1]->winner); // Track loser
                } else {
                    match->winner = leafNodes[i + 1]->winner;
                    losers.push_back(leafNodes[i]->winner); // Track loser
                }

                nextRound.push_back(match);
            } else {
                // Odd number of competitors - this one gets a bye
                nextRound.push_back(leafNodes[i]);
            }
        }

        leafNodes = nextRound;
    }

    return leafNodes[0]; // Return the championship node
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::buildLosersBracket(std::vector<T*>& losers) {
    if (losers.empty()) return nullptr;

    // Create a bracket for losers similar to single elimination
    std::vector<TournamentNode<T>*> nodes;

    // Create leaf nodes for each loser
    for (T* loser : losers) {
        TournamentNode<T>* node = new TournamentNode<T>(loser);
        std::cout << "Created leaf node for loser: " << loser->name << std::endl;
        nodes.push_back(node);
    }

    // Build the losers bracket tree bottom-up
    while (nodes.size() > 1) {
        std::vector<TournamentNode<T>*> nextRound;

        for (size_t i = 0; i < nodes.size(); i += 2) {
            if (i + 1 < nodes.size()) {
                // Create match between two losers
                TournamentNode<T>* match = new TournamentNode<T>();
                match->right = nodes[i];
                match->left = nodes[i + 1];

                // Determine winner based on scream power
                if (*nodes[i]->winner > *nodes[i + 1]->winner) {
                    match->winner = nodes[i]->winner;
                } else {
                    match->winner = nodes[i + 1]->winner;
                }

                nextRound.push_back(match);
            } else {
                // Odd number of competitors - this one gets a bye
                nextRound.push_back(nodes[i]);
            }
        }

        nodes = nextRound;
    }

    return nodes[0]; // Return the championship node of losers bracket
}

template <typename T>
void TournamentTree<T>::runSingleElimination(std::vector<T*>& competitors) {
    losers.clear();
    root = buildSingleEliminationTree(competitors);
}

template <typename T>
void TournamentTree<T>::runDoubleElimination(std::vector<T*>& competitors) {
    losers.clear();

    // Build winners bracket
    TournamentNode<T>* winnersRoot = buildSingleEliminationTree(competitors);

    // Save the championship structure by duplicating it at each level
    // This creates the leaf nodes showing the individual match-ups in expected format
    TournamentNode<T>* champNode = new TournamentNode<T>(winnersRoot->winner);
    champNode->left = winnersRoot;

    // Build losers bracket with the tracked losers
    // Exclude the winner of winners bracket from losers
    std::vector<T*> losersCopy = losers;
    TournamentNode<T>* losersRoot = buildLosersBracket(losersCopy);

    // Connect winners and losers brackets under the root
    root = new TournamentNode<T>();
    root->left = champNode;
    root->right = losersRoot;

    // Championship is winner of winners bracket
    root->winner = winnersRoot->winner;
}





#endif
