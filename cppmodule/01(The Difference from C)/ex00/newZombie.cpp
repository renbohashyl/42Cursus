#include "Zombie.hpp"

Zombie	*newZombie(std::string name)
{
	Zombie *bar = new Zombie(name);
	return (bar);
}