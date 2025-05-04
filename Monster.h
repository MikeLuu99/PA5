// Monster.h
#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
public:
    std::string name;
    int screamPowerLevel;

    // Constructor
    Monster(std::string name, int power); // Initialize monster with name and power

    // Comparison operators for determining winners
    bool operator>(const Monster& other) const;
    bool operator<(const Monster& other) const;
    bool operator==(const Monster& other) const;
};

#endif
