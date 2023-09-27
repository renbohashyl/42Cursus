#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed(void) : fixed_point_num(0) { std::cout << "Default constructor called" << std::endl; }

Fixed::Fixed(const Fixed& copy) : fixed_point_num(copy.fixed_point_num) { std::cout << "Copy constructor called" << std::endl; }

Fixed& Fixed::operator=(const Fixed &copy_assign) {
	if (this != &copy_assign)
		this->fixed_point_num = copy_assign.fixed_point_num;
	std::cout << "Copy assignment operator called" << std::endl;
	return (*this);
}

int		Fixed::getRawBits(void) const { return (this->fixed_point_num); }
void	Fixed::setRawBits(int const raw) { this->fixed_point_num = raw; }
Fixed::~Fixed(void) { std::cout << "Destructor called" << std::endl; }