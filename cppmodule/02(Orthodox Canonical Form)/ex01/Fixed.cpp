#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed(void) : fixed_point_num(0) { std::cout << "Default constructor called" << std::endl; }

Fixed::Fixed(const int setValue) : fixed_point_num(setValue << this->fractional_bits) { std::cout << "Int constructor called" << std::endl; }

Fixed::Fixed(const float setValue) : fixed_point_num(roundf(setValue * (1 << this->fractional_bits))) { std::cout << "Float constructor called" << std::endl; }

Fixed::Fixed(const Fixed& copy) : fixed_point_num(copy.fixed_point_num) { std::cout << "Copy constructor called" << std::endl; }

Fixed& Fixed::operator=(const Fixed &copy_assign) {
	if (this != &copy_assign)
		this->fixed_point_num = copy_assign.fixed_point_num;
	std::cout << "Copy assignment operator called" << std::endl;
	return (*this);
}

int		Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return (this->fixed_point_num);
}

void	Fixed::setRawBits(int const raw) {
	std::cout << "setRawBits member function called" << std::endl;
	this->fixed_point_num = raw;
}

float	Fixed::toFloat(void) const { return ((float)(this->fixed_point_num) / (1 << this->fractional_bits)); }

int		Fixed::toInt(void) const { return (this->fixed_point_num >> this->fractional_bits); }

Fixed::~Fixed(void) { std::cout << "Destructor called" << std::endl; }

std::ostream& operator<< (std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}