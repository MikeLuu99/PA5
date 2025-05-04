/*
* Full name: Mike Luu
* Full name: Lance Nguyen
* Student ID: 2451334
* Chapman email: duluu@chapman.edu lannguyen@chapman.edu
* Course: CPSC 350 - 04 CPSC 350 - 01
* Assignment: Programming Assignment 5
*/

#ifndef TOURNAMENT_NODE_H
#define TOURNAMENT_NODE_H

// TournamentNode represents a single match in the tournament tree
// Each node contains the winner of the match and references to competing participants
template <typename T>
class TournamentNode {
public:
    T* winner;                    // Points to competitor who won this match
    TournamentNode<T>* left;      // Left branch competitor
    TournamentNode<T>* right;     // Right branch competitor

    // Default constructor: Creates empty match node
    TournamentNode() {
        winner = nullptr;
        left = nullptr;
        right = nullptr;
    }

    // Constructor with winner: Creates leaf node (no children)
    TournamentNode(T* w) {
        winner = w;
        left = nullptr;
        right = nullptr;
    }

    // Destructor: Recursively deletes all child nodes
    ~TournamentNode() {
        delete left;
        delete right;
    }
};

#endif // TOURNAMENT_NODE_H
