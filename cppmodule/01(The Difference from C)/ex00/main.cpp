#include "Zombie.hpp"
#include <iostream>

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

int	main()
{
	Zombie	*foo(newZombie("foo"));
	foo->announce();
	randomChump("bar");
	delete foo;
}