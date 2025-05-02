#ifndef TOURNAMENT_TREE_H
#define TOURNAMENT_TREE_H

#include <vector>
#include "TournamentNode.h"
#include "Monster.h"

template <typename T>
class TournamentTree {
public:
    TournamentTree(const std::vector<Monster<T>*>& competitors);
    ~TournamentTree();
    
    void singleElimination();
    void doubleElimination();
    void saveTreeAsDot(const std::string& filename) const;

private:
    TournamentNode<T>* buildSingleEliminationRound(std::vector<Monster<T>*>& competitors);
    TournamentNode<T>* buildDoubleEliminationRound(std::vector<Monster<T>*>& winners, std::vector<Monster<T>*>& losers);
    void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) const;
    
    TournamentNode<T>* root;
    std::vector<Monster<T>*> competitors;
};

#endif