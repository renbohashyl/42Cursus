#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name);

int	main()
{
	Zombie	*horde(zombieHorde(10, "foo"));
	delete []horde;
}