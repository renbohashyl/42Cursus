#include <iostream>

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
		Fixed &operator=(const Fixed &copy_assign);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
		~Fixed(void);
};

std::ostream& operator<< (std::ostream &os, const Fixed &fixed);