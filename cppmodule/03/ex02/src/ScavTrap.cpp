#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(void) : ClapTrap("SC4V-TP", 100, 50, 20) {
	std::cout << "SC4V-TP : " << this->name <<" is here!" << std::endl;
}

ScavTrap::ScavTrap(const std::string setName) : ClapTrap(setName, 100, 50, 20)  {
	std::cout << "SC4V-TP : " << this->name <<" is here!" << std::endl;
}

ScavTrap::ScavTrap(const std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG)
	: ClapTrap(setName, setHP, setMP, setDMG) {
	std::cout << "SC4VTP : " << this->name << " is here!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& copy)
	: ClapTrap(copy.name, copy.hp, copy.mp, copy.dmg) {
	std::cout << "SC4V-TP : " << this->name << " is here! and there is the doppleganger!!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& copy_assign) {
	std::cout << "SC4V-TP : " << this->name << " will be replica of " << copy_assign.name << std::endl;
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

void	ScavTrap::attack(const std::string& target)
{
	if (this->mp <= 0 || this->hp <= 0) {
		std::cout << "attack failed" << std::endl;
		return ;
	}
	this->mp -= 1;
	std::cout << "SC4V-TP \""<< this->name << "\" attacks \"" << target << "\", causing " <<  this->dmg << " points of damage!" << std::endl;
}

void	ScavTrap::takeDamage(unsigned int amount)
{
	if (this->hp <= 0)
		return ;
	if (amount > this->hp)
		amount = this->hp;
	this->hp -= (amount);
}

void	ScavTrap::beRepaired(unsigned int amount)
{
	if (this->mp <= 0 || this->hp <= 0) {
		std::cout << "repair failed" << std::endl;
		return ;
	}
	if (this->hp + amount > maxhp)
		amount = maxhp - this->hp;
	this->hp += amount;
	this->mp -= 1;
	std::cout << "SC4V-TP \"" << this->name << "\" used its energy and " << amount << " points repaired!" << std::endl;
}

void	ScavTrap::guardGate(void) { std::cout << this->name << " says : It's a VERY important duty, as I'm not to let ANYONE in through here! Unless, of course, you're here as fresh meat for the recruitment grinder!" << std::endl; }

ScavTrap::~ScavTrap(void) { std::cout << "SC4V-TP : " << this->name << " has broken" << std::endl; }