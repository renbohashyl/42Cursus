#include <iostream>
#include <vector>
#include <string>
#include "easyfind.hpp"

#define CUSTOM_NBR 5
#define CUSTOM_CHAR 'A'
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"

int main () {
	std::vector<int> intcon(5);
	std::string strcon("asdf asdf");

	//intcon.push_back(CUSTOM_NBR);

	try {
		easyfind(intcon, 0);
		std::cout << COLOR_GREEN << "found 0" << std::endl;
		easyfind(intcon, CUSTOM_NBR);
		std::cout << COLOR_GREEN << "found " << CUSTOM_NBR << std::endl;
	}
	catch (const std::exception & e) {
		std::cerr << COLOR_YELLOW << e.what() << std::endl;
	}

	strcon.append("CUSTOM_CHAR");

	try {
		easyfind(strcon, 'a');
		std::cout << COLOR_GREEN << "found \'a\'" << std::endl;
		easyfind(strcon, CUSTOM_CHAR);
		std::cout << COLOR_GREEN << "found " << CUSTOM_CHAR << std::endl;
	}
	catch (const std::exception & e) {
		std::cerr << COLOR_YELLOW << e.what() << std::endl;
	}
}