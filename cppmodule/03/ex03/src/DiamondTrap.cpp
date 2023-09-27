#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap(void) : name("Horrible_Hybrid") {
	ClapTrap::name = this->name + "_clap_name";
	this->hp = FragTrap::FragHp;
	this->mp = ScavTrap::ScavMp;
	this->dmg = FragTrap::FragDmg;
	std::cout << "Horrible Hybrid : " << this->name << " : PREPARE for DEATH " << std::endl;
}

DiamondTrap::DiamondTrap(std::string setName) : name(setName) {
	ClapTrap::name = this->name + "_clap_name";
	this->hp = FragTrap::FragHp;
	this->mp = ScavTrap::ScavMp;
	this->dmg = FragTrap::FragDmg;
	std::cout << "Horrible Hybrid : " << this->name << " : PREPARE for DEATH " << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& copy_assign) {
	std::cout << "Horrible Hybrid : " << this->name << " will be replica of " << copy_assign.name << std::endl;
	if (this != &copy_assign)
	{
		this->name = copy_assign.name;
		this->hp = copy_assign.hp;
		this->mp = copy_assign.mp;
		this->dmg = copy_assign.dmg;
	}
	return (*this);
}

void	DiamondTrap::whoAmI(void) {
	std::cout << "this->name is " << this->name << std::endl;
	std::cout << "this->ClapTrap::name is " << ClapTrap::name << std::endl;
	std::cout << "hp : " << this->hp << std::endl;
	std::cout << "mp : " << this->mp << std::endl;
	std::cout << "dmg : " << this->dmg << std::endl;
}

void	DiamondTrap::attack(std::string target) { ScavTrap::attack(target); }

DiamondTrap::~DiamondTrap(void) { std::cout << "Horrible Hybrid : " << this->name << " is broken!" << std::endl; }