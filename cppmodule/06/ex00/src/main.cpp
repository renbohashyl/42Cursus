#include <iostream>
#include <string>
#include <climits>
#include <cstdlib>

int	main (const int ac, char **av) {
	if (ac != 2)
		return (0);

	double temp = std::strtod(av[1], NULL);

	//char
	std::cout << "char: ";
	if (temp >= 0x20 && temp < 0x7F) {
		std::cout << static_cast<char>(temp);
	} else if (temp > 0 && (temp < 0x20 || temp == 0x7F)) {
		std::cout << "Non displayable";
	} else { std::cout << "impossible"; }
	std::cout << std::endl;

	//int
	std::cout << "int: ";
	if (temp == temp && temp >= INT_MIN && temp <= INT_MAX) {
		std::cout << static_cast<int>(temp);
	} else {
		std::cout << "impossible";
	}
	std::cout << std::endl;

	//float
	std::cout << "float: " << static_cast<float>(temp);
	if (temp == static_cast<int>(temp))
		std::cout << ".0";
	std::cout << 'f' << std::endl;

	//double
	std::cout << "double: " << temp;
	if (temp == static_cast<int>(temp))
		std::cout << ".0";
	std::cout << std::endl;
	return (0);
}