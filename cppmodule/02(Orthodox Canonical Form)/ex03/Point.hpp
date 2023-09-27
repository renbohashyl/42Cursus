#include "Fixed.hpp"

class Point {
	private:
		Fixed const	x;
		Fixed const	y;
	public:
		Point(void);
		Point(const Point& copy);
		Point(const float setX, const float setY);
		Point& operator=(const Point& copy_assign);
		Point operator-(const Point& operland) const;
		float cross(const Point& other) const;
		~Point(void);
};