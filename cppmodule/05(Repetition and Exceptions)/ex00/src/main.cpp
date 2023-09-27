#include "Bureaucrat.hpp"

int	main()
{
	Bureaucrat def;

	std::cout << def << std::endl;
	try {
		def.decrease_grade();
		def.decrease_grade();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	try {
		def.increase_grade();
		std::cout << def.getGrade() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}