#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <string>

class WrongAnimal {
	protected:
		std::string	type;
	public:
		WrongAnimal(void);
		WrongAnimal(std::string setName);
		WrongAnimal(const WrongAnimal& copy);
		WrongAnimal& operator=(const WrongAnimal& copy_assign);
		const std::string& getType(void) const;
		void	makeSound(void) const;
		~WrongAnimal(void);
};

#endif