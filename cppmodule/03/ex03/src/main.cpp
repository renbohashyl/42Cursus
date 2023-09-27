#include "DiamondTrap.hpp"
#include <iostream>

int	main()
{
	DiamondTrap	jack;

	std::cout << "\n===================Called_whoAmI===================" << std::endl;
	jack.whoAmI();
	std::cout << "===================================================" << std::endl;
	std::cout << "\n===================Called_attack===================" << std::endl;
	jack.attack("the Rocks");
	std::cout << "===================================================\n" << std::endl;
	return (0);
}