#include "Weapon.hpp"

Weapon::Weapon(void) { }

Weapon::Weapon(std::string weaponname) { this->name = weaponname; }

std::string	&Weapon::getType(void) { return (this->name); }

void	Weapon::setType(std::string weaponname) { this->name = weaponname; }

Weapon::~Weapon(void) { }