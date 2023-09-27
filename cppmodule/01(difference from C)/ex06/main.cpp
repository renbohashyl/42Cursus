#include "Harl.hpp"
#include <iostream>

int	main(const int argc, const char **av)
{
	if (argc != 2)
		return (0);
	std::string	mode[4]={"DEBUG", "INFO", "WARNING", "ERROR"};
	int	index;
	for (index = 0; index < 4; index++) {
		if (mode[index] == av[1])
			break ;
	}
	Harl harl;
	switch (index)
	{
		case 0 :
			harl.complain("debug");
		case 1 :
			harl.complain("info");
		case 2 :
			harl.complain("warning");
		case 3 :
			harl.complain("error");
			break ;
		default:
			std::cout << "[ unexcepted input, try again ]" << std::endl;
			break;
	}
}