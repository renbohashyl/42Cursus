#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

void	sign_and_execute(AForm *theform)
{
	Bureaucrat high("priest", 1);

	try
	{
		high.signForm(*theform);
		high.executeForm(*theform);
	}
	catch (std::exception& e) { }
	delete (theform);
}

void	do_make_and_test(const std::string form, const std::string target)
{
	Intern	someone;
	AForm	*theform;

	try
	{
		theform = someone.makeForm(form, target);
		sign_and_execute(theform);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

int	main()
{
	std::string exist[3] = {"presidential pardon", "robotomy request", "shrubbery creation"};
	std::string target[3] = {"jbak", "someone", "else"};

	for (int i = 0; i < 3; i++)
		do_make_and_test(exist[i], target[i]);
	//do_make_and_test("something_to_test", "something_to_test");
	//system("leaks At_least_this_beats_coffee-making");
}