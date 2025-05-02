#ifndef TOURNAMENT_NODE_H
#define TOURNAMENT_NODE_H

#include "Monster.h"

template <typename T>
class TournamentNode {
public:
    TournamentNode();
    TournamentNode(Monster<T>* leftMonster, Monster<T>* rightMonster);
    ~TournamentNode();
    
    // Node structure
    TournamentNode<T>* left;
    TournamentNode<T>* right;
    
    // Match data
    Monster<T>* leftMonster;
    Monster<T>* rightMonster;
    Monster<T>* winner;
    
    // Determine winner of this node's match
    void determineWinner();
};

#endif