#ifndef MONSTER_H
#define MONSTER_H

#include <string>

template <typename T>
class Monster {
  public:
    Monster(std::string name, T screamPowerLevel);
    ~Monster();
    bool compareScreamPower(const Monster<T>& other) const;
    std::string getName() const { return name; }
    T getScreamPower() const { return screamPowerLevel; }

    // Made public for DOT file generation
    std::string name;
    T screamPowerLevel;
};

#endif
