#include "Fixed.hpp"

Fixed::Fixed(void) : fixed_point_num(0) { }
Fixed::Fixed(const Fixed& copy) : fixed_point_num(copy.fixed_point_num) { }
Fixed::Fixed(const int setValue) : fixed_point_num(setValue << this->fractional_bits) { }
Fixed::Fixed(const float setValue) : fixed_point_num(roundf(setValue * (1 << this->fractional_bits))) { }
float	Fixed::toFloat(void) const { return ((float)(this->fixed_point_num) / (1 << this->fractional_bits)); }
int		Fixed::toInt(void) const { return (this->fixed_point_num >> this->fractional_bits); }

Fixed &Fixed::operator=(const Fixed &copy_assignment) {
	if (this != &copy_assignment)
		this->fixed_point_num = copy_assignment.fixed_point_num;
	return (*this);
}

Fixed &Fixed::operator=(const float setValue) {
	this->fixed_point_num = roundf(setValue * (1 << this->fractional_bits));
	return (*this);
}

Fixed &Fixed::operator=(const int setValue) {
	this->fixed_point_num = setValue << this->fractional_bits;
	return (*this);
}

bool	Fixed::operator==(const Fixed &compTarget) const { return (this->toFloat() == compTarget.toFloat()); }
bool	Fixed::operator>(const Fixed &compTarget) const { return (this->toFloat() > compTarget.toFloat()); }
bool	Fixed::operator<(const Fixed &compTarget) const { return (this->toFloat() < compTarget.toFloat()); }
bool	Fixed::operator>=(const Fixed &compTarget) const { return (this->toFloat() >= compTarget.toFloat()); }
bool	Fixed::operator<=(const Fixed &compTarget) const { return (this->toFloat() <= compTarget.toFloat()); }
bool	Fixed::operator!=(const Fixed &compTarget) const { return (this->toFloat() != compTarget.toFloat()); }

Fixed Fixed::operator+(const Fixed &operland) const {
	Fixed	tmp;

	tmp.setRawBits(this->fixed_point_num + operland.fixed_point_num);
	return (tmp);
}

Fixed Fixed::operator-(const Fixed &operland) const {
	Fixed	tmp;

	tmp.setRawBits(this->fixed_point_num - operland.fixed_point_num);
	return (tmp);
}

Fixed Fixed::operator*(const Fixed &operland) const {
	Fixed	tmp;

	tmp.setRawBits(roundf((this->toFloat() * operland.toFloat()) * (1 << this->fractional_bits)));
	return (tmp);
}

Fixed Fixed::operator/(const Fixed &operland) const {
	Fixed	tmp;

	if (operland.toFloat() == 0)
		return (*this);
	tmp.setRawBits(roundf((this->toFloat() / operland.toFloat()) * (1 << this->fractional_bits)));
	return (tmp);
}

Fixed Fixed::operator+=(const Fixed &operland) {
	this->setRawBits(this->fixed_point_num + operland.fixed_point_num);
	return (*this);
}
Fixed Fixed::operator-=(const Fixed &operland) {
	this->setRawBits(this->fixed_point_num - operland.fixed_point_num);
	return (*this);
}
Fixed Fixed::operator*=(const Fixed &operland) {
	this->setRawBits(this->toFloat() * operland.fixed_point_num);
	return (*this);
}

Fixed Fixed::operator/=(const Fixed &operland) {
	this->setRawBits(this->toFloat() / operland.fixed_point_num);
	return (*this);
}

Fixed &Fixed::operator++(void)
{
	(this->fixed_point_num)++;
	return (*this);
}
Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);

	operator++();
	return (tmp);
}
Fixed &Fixed::operator--(void)
{
	(this->fixed_point_num)--;
	return (*this);
}
Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);

	operator--();
	return (tmp);
}

float	Fixed::min(Fixed &a, Fixed &b) { return ((a < b) * (a.toFloat() + (b < a) * (b.toFloat()))); }
float	Fixed::min(const Fixed &a, const Fixed &b) { return ((a < b) * a.toFloat() + (b < a) * (b.toFloat())); }
float	Fixed::max(Fixed &a, Fixed &b) { return ((a > b) * (a.toFloat() + (b > a) * (b.toFloat()))); }
float	Fixed::max(const Fixed &a, const Fixed &b) { return ((a > b) * a.toFloat() + (b > a) * (b.toFloat())); }
int		Fixed::getRawBits(void) const { return (this->fixed_point_num); }
void	Fixed::setRawBits(int const raw) { this->fixed_point_num = raw; }

Fixed::~Fixed(void) { }

std::ostream& operator<< (std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}