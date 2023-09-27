#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(void) {
	this->name = "SC4V-TP";
	this->hp = 100;
	this->maxhp = 100;
	this->mp = 50;
	this->dmg = 20;
	std::cout << "SC4V-TP : " << this->name <<" is here!" << std::endl;
}

ScavTrap::ScavTrap(std::string setName) {
	this->name = setName;
	this->hp = 100;
	this->maxhp = 100;
	this->mp = 50;
	this->dmg = 20;
	std::cout << "SC4V-TP : " << this->name <<" is here!" << std::endl;
}

ScavTrap::ScavTrap(std::string setName, unsigned int setHP, unsigned int setMP, unsigned int setDMG) {
	this->name = setName;
	this->hp = setHP;
	this->maxhp = setHP;
	this->mp = setMP;
	this->dmg = setDMG;
	std::cout << "SC4VTP : " << this->name << " is here!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& copy) {
	*this = copy;
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
	if (this->mp <= 0 || this->hp <= 0)
		return ;
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
	if (this->mp <= 0 || this->hp <= 0)
		return ;
	if (this->hp + amount > maxhp)
		amount = maxhp - this->hp;
	this->hp += amount;
	this->mp -= 1;
	std::cout << "SC4V-TP \"" << this->name << "\" used its energy and " << amount << " points repaired!" << std::endl;
}

void	ScavTrap::guardGate(void) { std::cout << this->name << " says : It's a VERY important duty, as I'm not to let ANYONE in through here! Unless, of course, you're here as fresh meat for the recruitment grinder!" << std::endl; }

ScavTrap::~ScavTrap(void) { std::cout << "SC4V-TP : " << this->name << " has broken" << std::endl; }