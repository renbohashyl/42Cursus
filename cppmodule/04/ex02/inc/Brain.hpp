#ifndef	BRAIN_HPP
# define BRAIN_HPP

#include <string>

class Brain
{
	private:
		enum { MAX_IDEAS = 100 };
		std::string	Ideas_[MAX_IDEAS];
	public:
		Brain();
		Brain(const Brain& copy);
		Brain& operator=(const Brain& operland);
		~Brain();
};

#endif