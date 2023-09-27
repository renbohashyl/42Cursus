#include "ClapTrap.hpp"
#include <iostream>

void	do_test(ClapTrap& jack, ClapTrap& phoenix)
{
	phoenix.attack("jack");
	jack.takeDamage(phoenix.getAttackDamage());
	jack.beRepaired(900);
	std::cout << std::endl;
}

int	main()
{
	ClapTrap jack("jack");
	ClapTrap phoenix("phoenix", 500, 500, 500);
	std::cout << "=============constructor complete=============" << std::endl << std::endl;

	do_test(phoenix, jack);
	do_test(jack, phoenix); //jack will be failed to repair, because he has no hp
	std::cout << "=============member function test complete=============" << std::endl << std::endl;

	jack = phoenix;
	jack.attack("rock");
	return (0);
}