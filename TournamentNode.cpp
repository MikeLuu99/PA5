#include "TournamentNode.h"

template <typename T>
TournamentNode<T>::TournamentNode() : left(nullptr), right(nullptr), 
    leftMonster(nullptr), rightMonster(nullptr), winner(nullptr) {
}

template <typename T>
TournamentNode<T>::TournamentNode(Monster<T>* leftMonster, Monster<T>* rightMonster) 
    : left(nullptr), right(nullptr), leftMonster(leftMonster), rightMonster(rightMonster), winner(nullptr) {
    determineWinner();
}

template <typename T>
TournamentNode<T>::~TournamentNode() {
    delete left;
    delete right;
}

template <typename T>
void TournamentNode<T>::determineWinner() {
    if (!rightMonster) {
        winner = leftMonster;  // Bye round
        return;
    }
    
    if (leftMonster->compareScreamPower(*rightMonster)) {
        winner = leftMonster;
    } else {
        winner = rightMonster;
    }
}

// Explicit template instantiation
template class TournamentNode<int>;
template class TournamentNode<double>;
template class TournamentNode<float>;