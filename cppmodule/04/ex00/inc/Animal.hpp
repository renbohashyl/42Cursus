#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>

class Animal {
	protected:
		std::string	Type_;
	public:
		Animal();
		Animal(const std::string name);
		Animal(const Animal& copy);
		Animal& operator=(const Animal& copy_assign);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const;
		virtual ~Animal(void);
};

#endif