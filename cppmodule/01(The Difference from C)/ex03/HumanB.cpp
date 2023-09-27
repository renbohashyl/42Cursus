#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string setname) : name(setname), weapon(NULL) { }

HumanB::HumanB(std::string setname, Weapon &setweapon) : name(setname), weapon(&setweapon) { }

void	HumanB::setWeapon(Weapon &weaponname) { this->weapon = &weaponname; }

void	HumanB::attack(void) const { std::cout << this->name << " attacks with their " << (*(this->weapon)).getType() << std::endl; }

HumanB::~HumanB(void) { }