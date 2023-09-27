class Fixed
{
	private:
		int	fixed_point_num;
		static const int fractional_bits = 8;
	public:
		Fixed(void);
		Fixed(const Fixed& copy);
		Fixed &operator=(const Fixed &copy_assignment);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		~Fixed(void);
};
