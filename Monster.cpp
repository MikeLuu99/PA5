#include "Monster.h"
#include <string>

template <typename T>
Monster<T>::Monster(std::string name, T screamPowerLevel) {
  this->name = name;
  this->screamPowerLevel = screamPowerLevel;
}

template <typename T>
Monster<T>::~Monster() {
}

template <typename T>
bool Monster<T>::compareScreamPower(const Monster<T>& other) const {
  return this->screamPowerLevel > other.screamPowerLevel;
}

// Explicit template instantiation for common types
template class Monster<int>;
template class Monster<double>;
template class Monster<float>;