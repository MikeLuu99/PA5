// Monster.cpp
#include "Monster.h"

Monster::Monster(std::string name, int power) : name(name), screamPowerLevel(power) {}

// Compare monsters based on scream power
bool Monster::operator>(const Monster& other) const {
    return screamPowerLevel > other.screamPowerLevel;
}

bool Monster::operator<(const Monster& other) const {
    return screamPowerLevel < other.screamPowerLevel;
}

bool Monster::operator==(const Monster& other) const {
    return name == other.name && screamPowerLevel == other.screamPowerLevel;
}
