#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(void) : name("CL4P-TP"), hp(10), maxhp(10), mp(10), dmg(0) {
	std::cout << "ClapTrap : " << this->name << " : Hi! Vault Hunter!" << std::endl;
}

ClapTrap::ClapTrap(std::string setName) : name(setName), hp(10), maxhp(10), mp(10), dmg(0) {
	std::cout << "ClapTrap : " << this->name << " : Hi! Vault Hunter!" << std::endl;
}

ClapTrap::ClapTrap(std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG) : name(setName), hp(setHP), maxhp(setHP), mp(setMP), dmg(setDMG) {
	std::cout << "ClapTrap : " << this->name << " : Hi! Vault Hunter!" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const& copy) : name(copy.name), hp(copy.hp), maxhp(copy.maxhp), mp(copy.mp), dmg(copy.dmg) {
	std::cout << "ClapTrap : " << this->name << " : Hi! doppleganger!" << std::endl;
}

ClapTrap& ClapTrap::operator=(ClapTrap const& copy_assign) {
	if (this != &copy_assign) {
		this->name = copy_assign.name;
		this->hp = copy_assign.hp;
		this->maxhp = copy_assign.maxhp;
		this->mp = copy_assign.mp;
		this->dmg = copy_assign.dmg;
	}
	std::cout << this->name << " is mass production of " << copy_assign.name << std::endl;
	return (*this);
}

void	ClapTrap::attack(const std::string& target)
{
	if (this->mp <= 0) {
		std::cout << this->name << " has failed to attack, because it has not enough energy" << std::endl;
		return ;
	}
	this->mp -= 1;
	std::cout << "ClapTrap \""<< this->name << "\" attacks \"" << target << "\", causing " <<  this->dmg << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->hp <= 0)
		return ;
	if (amount > this->hp)
		amount = this->hp;
	this->hp -= (amount);
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->mp <= 0) {
		std::cout << this->name << " has failed to Repair, because it has not enough energy" << std::endl;
		return ;
	}
	else if (this->hp + amount > this->maxhp)
		amount = this->maxhp - this->hp;
	this->hp += amount;
	this->mp -= 1;
	std::cout << "ClapTrap \"" << this->name << "\" used its energy and " << amount << " points repaired!" << std::endl;
}

int		ClapTrap::getAttackDamage(void) const { return(this->dmg); }

ClapTrap::~ClapTrap() { std::cout << "ClapTrap : " << this->name << " has broken" << std::endl; }