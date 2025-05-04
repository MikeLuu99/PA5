/*
* Full name: Mike Luu
* Full name: Lance Nguyen
* Student ID: 2451334
* Chapman email: duluu@chapman.edu lannguyen@chapman.edu
* Course: CPSC 350 - 04 CPSC 350 - 01
* Assignment: Programming Assignment 5
*/

#ifndef MONSTER_H
#define MONSTER_H

#include <string>

// Monster class represents a competitor in the scare tournament
// Each monster has a name and scream power level that determines their strength
class Monster {
public:
    std::string name;              // Monster's identifier/name
    int screamPowerLevel;          // Monster's power level for competition

    // Constructor: Creates a monster with given name and power level
    Monster(std::string name, int power);

    // Comparison operators to determine tournament winners based on scream power
    bool operator>(const Monster& other) const;  // Returns true if this monster has higher power
    bool operator<(const Monster& other) const;  // Returns true if this monster has lower power
    bool operator==(const Monster& other) const; // Returns true if monsters are identical
};

#endif
