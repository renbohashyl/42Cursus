#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string setname, Weapon &setweapon) : name(setname), weapon(setweapon) { }

void	HumanA::attack(void) const { std::cout << this->name << " attacks with their " << (this->weapon).getType() << std::endl; }

HumanA::~HumanA(void) { }