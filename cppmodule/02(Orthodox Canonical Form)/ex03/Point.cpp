#include "Point.hpp"

Point::Point() : x(0), y(0) { }
Point::Point(const float setX, const float setY) : x(setX), y(setY) { }
Point::Point(const Point& copy) : x(copy.x), y(copy.y) {  }

Point& Point::operator=(const Point& copy_assign) {
	(void)copy_assign;
	return (*this);
}

Point	Point::operator-(const Point &operland) const {
	Fixed 	x;
	Fixed 	y;

	x = (this->x - operland.x);
	y = (this->y - operland.y);
	Point	tmp(x.toFloat(), y.toFloat());
	return (tmp);
}

float Point::cross(const Point& other) const { return ((this->x * other.y).toFloat() - (this->y * other.x).toFloat()); }

Point::~Point(void) { }