#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() { }

Zombie::Zombie(std::string name) { this->name = name; }

void	Zombie::change_name(std::string name) { this->name = name; }

void	Zombie::announce(void) { std::cout << this->name << ": " << "BraiiiiiiinnnzzzZ...\n"; }

Zombie::~Zombie() { std::cout << "\"" << this->name << "\" zombie has been deleted\n"; }