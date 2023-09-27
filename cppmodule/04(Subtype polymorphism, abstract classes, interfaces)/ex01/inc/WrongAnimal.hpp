#ifndef WrongAnimal_HPP
# define WrongAnimal_HPP

#include <string>

class WrongAnimal {
	protected:
		std::string	type;
	public:
		WrongAnimal(void);
		WrongAnimal(const std::string setName);
		WrongAnimal(const WrongAnimal& copy);
		WrongAnimal& operator=(const WrongAnimal& copy_assign);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const;
		virtual ~WrongAnimal(void);
};

#endif