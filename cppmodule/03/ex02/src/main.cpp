#include "FragTrap.hpp"
#include <iostream>

int	main()
{
	FragTrap jack("jack");

	std::cout << "\n===============Called_highFivesGuys===============" << std::endl;
	jack.highFivesGuys();
	std::cout << "==================================================\n" << std::endl;
	return (0);
}