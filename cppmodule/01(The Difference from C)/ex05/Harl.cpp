#include "Harl.hpp"
#include <iostream>

Harl::Harl(void) { }

void	Harl::debug(void) { std::cout << "This is DEBUG level" << std::endl; }
void	Harl::info(void) { std::cout << "This is INFO level" << std::endl; }
void	Harl::warning(void) { std::cout << "This is WARNING level" << std::endl; }
void	Harl::error(void) { std::cout << "This is ERROR level" << std::endl; }

void	Harl::complain(std::string level)
{
	void	(Harl::*fp[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string	harl[4] = {"debug", "info", "warning", "error"};
	unsigned int	index(10);

	for (int i = 0; i < 4; i++) {
		if (harl[i] == level)
			index = i;
	}
	if (index > 3)
		return ;
	(this->*fp[index])();
}

Harl::~Harl(void) { }