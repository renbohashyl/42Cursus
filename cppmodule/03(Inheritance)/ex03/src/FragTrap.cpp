#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap(void) {
	this->name = "player";
	this->hp = 100;
	this->maxhp = 100;
	this->mp = 100;
	this->dmg = 30;
	std::cout << "FragTrap (Vault Hunter) : " << this->name << " is here! " << std::endl;
}
FragTrap::FragTrap(std::string setName) {
	this->name = setName;
	this->hp = 100;
	this->maxhp = 100;
	this->mp = 100;
	this->dmg = 30;
	std::cout << "FragTrap (Vault Hunter) : " << this->name << " is here! " << std::endl;
}

FragTrap::FragTrap(std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG) {
	this->name = setName;
	this->hp = setHP;
	this->maxhp = setHP;
	this->mp = setMP;
	this->dmg = setDMG;
	std::cout << "FragTrap (Vault Hunter) : " << this->name << " is here! " << std::endl;
}

FragTrap::FragTrap(FragTrap &copy) {
	*this = copy;
	std::cout << this->name << " : What!!! it can't be... it must be a bug!" << std::endl;
}

FragTrap& FragTrap::operator=(FragTrap &copy_assign) {
	std::cout << "FragTrap (Vault Hunter) : " << this->name << " will be replica of " << copy_assign.name << std::endl;
	if (this != &copy_assign)
	{
		this->name = copy_assign.name;
		this->hp = copy_assign.hp;
		this->maxhp = copy_assign.maxhp;
		this->mp = copy_assign.mp;
		this->dmg = copy_assign.dmg;
	}
	return (*this);
}

void	FragTrap::highFivesGuys(void) { std::cout << "Let's get this party started!" << std::endl;}

FragTrap::~FragTrap(void) { std::cout << "FragTrap : " << this->name << " has left a gmae" << std::endl; }