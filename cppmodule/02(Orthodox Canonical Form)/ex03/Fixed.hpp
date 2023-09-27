#include <iostream>
#include <string>

class Fixed
{
	private:
		int	fixed_point_num;
		static const int fractional_bits = 8;
	public:
		Fixed(void);
		Fixed(const int setValue);
		Fixed(const float setValue);
		Fixed(const Fixed& copy);
		Fixed &operator=(const Fixed &copy_assignment);
		Fixed &operator=(const float setValue);
		Fixed &operator=(const int setValue);
		bool operator>(const Fixed &compTarget) const;
		bool operator<(const Fixed &compTarget) const;
		bool operator>=(const Fixed &compTarget) const;
		bool operator<=(const Fixed &compTarget) const;
		bool operator==(const Fixed &compTarget) const;
		bool operator!=(const Fixed &compTarget) const;
		Fixed operator+(const Fixed &operland) const;
		Fixed operator-(const Fixed &operland) const;
		Fixed operator*(const Fixed &operland) const;
		Fixed operator/(const Fixed &operland) const;
		Fixed operator+=(const Fixed &operland);
		Fixed operator-=(const Fixed &operland);
		Fixed operator*=(const Fixed &operland);
		Fixed operator/=(const Fixed &operland);
		Fixed &operator++(void);
		Fixed operator++(int);
		Fixed &operator--(void);
		Fixed operator--(int);
		static float	min(Fixed &a, Fixed &b);
		static float	min(const Fixed &a, const Fixed &b);
		static float	max(Fixed &a, Fixed &b);
		static float	max(const Fixed &a, const Fixed &b);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
		~Fixed(void);
};

std::ostream& operator<< (std::ostream &os, const Fixed &fixed);