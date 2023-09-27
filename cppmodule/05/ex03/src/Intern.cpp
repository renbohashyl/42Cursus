#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern() { }

AForm* Intern::makeForm(const std::string form_name, const std::string target)
{
	std::string exist_name[3] = {"presidential pardon", "robotomy request", "shrubbery creation"};
	int	index(10);

	for (int i = 0; i < 3; i++) {
		if (exist_name[i] == form_name) {
			index = i;
			break ;
		}
	}

	switch (index)
	{
		case 0 :
			std::cout << "Intern creates PresidentialPardonForm" << std::endl;
			return (new PresidentialPardonForm(target));
		case 1 :
			std::cout << "Intern creates RobotomyRequestForm" << std::endl;
			return (new RobotomyRequestForm(target));
		case 2 :
			std::cout << "Intern creates ShrubberyCreationForm" << std::endl;
			return (new ShrubberyCreationForm(target));
		default :
			throw(Intern::ItDoesNotExist());
	}
	return (NULL);
}

Intern::~Intern() { }