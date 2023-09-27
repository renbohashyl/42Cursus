#include "Harl.hpp"

int	main(void)
{
	Harl	harl;
	std::string	level[4] = {"debug", "info", "warning", "error"};

	for (int i = 0; i < 20; i++)
		harl.complain(level[i % 4]);
	harl.complain("dayum");
}