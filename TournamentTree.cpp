#include "TournamentTree.h"
#include <fstream>
#include <iostream>

template <typename T>
TournamentTree<T>::TournamentTree(const std::vector<Monster<T>*>& competitors)
: root(nullptr), competitors(competitors) {
}

template <typename T>
TournamentTree<T>::~TournamentTree() {
  delete root;
}

template <typename T>
void TournamentTree<T>::singleElimination() {
  std::vector<Monster<T>*> currentCompetitors = competitors;
  root = buildSingleEliminationRound(currentCompetitors);
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::buildSingleEliminationRound(std::vector<Monster<T>*>& competitors) {
  if (competitors.empty()) {
    return nullptr;
  }

  if (competitors.size() == 1) {
    return new TournamentNode<T>(competitors[0], nullptr);
  }

  std::vector<Monster<T>*> nextRound;
  std::vector<TournamentNode<T>*> currentRound;

  // Create matches for this round
  for (size_t i = 0; i < competitors.size(); i += 2) {
    Monster<T>* leftMonster = competitors[i];
    Monster<T>* rightMonster = (i + 1 < competitors.size()) ? competitors[i + 1] : nullptr;

    TournamentNode<T>* match = new TournamentNode<T>(leftMonster, rightMonster);
    nextRound.push_back(match->winner);
    currentRound.push_back(match);
  }

  // If we have more than one winner, create the next round
  if (nextRound.size() > 1) {
    TournamentNode<T>* nextRoundRoot = buildSingleEliminationRound(nextRound);

    // Connect the winners
    for (size_t i = 0; i < currentRound.size(); i += 2) {
      if (i/2 < currentRound.size()/2) {
        nextRoundRoot->left = currentRound[i];
        if (i + 1 < currentRound.size()) {
          nextRoundRoot->right = currentRound[i + 1];
        }
      }
    }

    return nextRoundRoot;
  }

  return currentRound[0];
}

template <typename T>
void TournamentTree<T>::doubleElimination() {
  std::vector<Monster<T>*> winners = competitors;
  std::vector<Monster<T>*> losers;

  // Build winners bracket
  TournamentNode<T>* winnersRoot = buildSingleEliminationRound(winners);

  // Build losers bracket
  if (!losers.empty()) {
    TournamentNode<T>* losersRoot = buildSingleEliminationRound(losers);

    // Create final match between winners and losers bracket champions
    root = new TournamentNode<T>(winnersRoot->winner, losersRoot->winner);
    root->left = winnersRoot;
    root->right = losersRoot;
  } else {
    root = winnersRoot;
  }
}

template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file for DOT output: " << filename << "\n";
    return;
  }

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
  file << "    node" << currentID << " [label=\"" << node->winner->name
    << " (Power: " << node->winner->screamPowerLevel << ")\"];\n";

  if (node->left) {
    int leftID = nodeID;
    saveTreeAsDotHelper(node->left, file, nodeID);
    file << "    node" << currentID << " -> node" << leftID << ";\n";
  }

  if (node->right) {
    int rightID = nodeID;
    saveTreeAsDotHelper(node->right, file, nodeID);
    file << "    node" << currentID << " -> node" << rightID << ";\n";
  }
}

// Explicit template instantiation
template class TournamentTree<int>;
template class TournamentTree<double>;
template class TournamentTree<float>;
