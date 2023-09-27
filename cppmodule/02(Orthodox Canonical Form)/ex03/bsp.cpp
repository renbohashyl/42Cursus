#include "Point.hpp"

bool	bsp( Point const &a, Point const &b, Point const &c, Point const &point)
{
	Point	ba(a - b);
	Point	cb(b - c);
	Point	ac(c - a);

	Point	ap(point - a);
	Point	bp(point - b);
	Point	cp(point - c);

	float ra = (ap.cross(ac));
	float rb = (bp.cross(ba));
	float rc = (cp.cross(cb));

	if ((ra > 0 && rb > 0 && rc > 0) || (ra < 0 && rb < 0 && rc < 0))
		return true;
	return false;
}