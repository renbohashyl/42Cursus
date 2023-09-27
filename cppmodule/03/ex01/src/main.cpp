#include "ScavTrap.hpp"
#include <iostream>

int	main()
{
	ScavTrap jack("jack");

	std::cout << "\n=================Called_functions=================" << std::endl;
	jack.attack("rocks");
	jack.takeDamage(jack.getAttackDamage());
	jack.beRepaired(jack.getAttackDamage());
	jack.guardGate();
	std::cout << "===================================================\n" << std::endl;
	return (0);
}