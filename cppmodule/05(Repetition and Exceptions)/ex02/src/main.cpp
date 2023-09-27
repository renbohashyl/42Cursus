#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

void	do_test(Bureaucrat& person)
{
	PresidentialPardonForm pardon(person.getName());
	RobotomyRequestForm robotomy(person.getName());
	ShrubberyCreationForm trees(person.getName());

	try {
		person.signForm(pardon);
		//if person successfully signed
		person.executeForm(pardon);
	}
	catch (std::exception& e) {
	}

	try {
		person.signForm(robotomy);
		//if person successfully signed
		person.executeForm(robotomy);
	}
	catch (std::exception& e) {
	}

	try {
		person.signForm(trees);
		//if person successfully signed
		person.executeForm(trees);
	}
	catch (std::exception& e) {
	}
}

int	main()
{
	Bureaucrat high("high", 1);
	Bureaucrat middle("middle", 75);
	Bureaucrat bottom("bottom", 150);

	do_test(high);
	std::cout << "==================================" << std::endl;
	do_test(middle);
	std::cout << "==================================" << std::endl;
	do_test(bottom);
}