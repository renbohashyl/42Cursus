#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	Form cannot("cannot", 1, 1);
	Bureaucrat lieutenent("kim", 2);
	std::cout << lieutenent << std::endl;
	std::cout << cannot << std::endl;
	try
	{
		lieutenent.signForm(cannot);
		std::cout << "is it failed?" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "did you caught? compiler?!" << std::endl;
	}
	std::cout << lieutenent << std::endl;
	std::cout << cannot << std::endl;
	try
	{
		lieutenent.increase_grade();
		lieutenent.signForm(cannot);
		std::cout << "Hey! i'm here" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "did you caught? compiler?!" << std::endl;
	}
	std::cout << lieutenent << std::endl;
	std::cout << cannot << std::endl;
	lieutenent.signForm(cannot);
	std::cout << cannot << std::endl;
}