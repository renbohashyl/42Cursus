#include "Fixed.hpp"

int main( void ) {

	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << "=================================" << std::endl;
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << b << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << (a > b) << std::endl;
	std::cout << (a < b) << std::endl;
	std::cout << (a >= b) << std::endl;
	std::cout << (a <= b) << std::endl;
	std::cout << (a == b) << std::endl;
	std::cout << (a != b) << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << a + b << std::endl;
	std::cout << a - b << std::endl;
	std::cout << a * b << std::endl;
	std::cout << a / b << std::endl;
	// std::cout << (0.0078125 / 10.1016) << std::endl;
	// std::cout << (0.0078125 / 10.1016) * 256 << std::endl;
	// std::cout << roundf((0.0078125 / 10.1016) * 256) << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << Fixed::min(a, b) << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;
	return (0);
}