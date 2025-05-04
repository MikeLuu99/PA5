/*
* Full name: Mike Luu
* Student ID: 2451334
* Chapman email: duluu@chapman.edu
* Course: CPSC 350 - 04
* Assignment: Programming Assignment 5
*/

#ifndef TOURNAMENT_NODE_H
#define TOURNAMENT_NODE_H

// Template class for tournament nodes
template <typename T>
class TournamentNode {
public:
    T* winner; // Competitor who won this match
    TournamentNode<T>* left; // Left child (competitor 1)
    TournamentNode<T>* right; // Right child (competitor 2)

    // Constructors and Destructor
    TournamentNode() {
        winner = nullptr;
        left = nullptr;
        right = nullptr;
    }

    TournamentNode(T* w) {
        winner = w;
        left = nullptr;
        right = nullptr;
    }

    ~TournamentNode() {
        delete left;
        delete right;
    }
};

#endif // TOURNAMENT_NODE_H
