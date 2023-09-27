#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include <string>

class AAnimal {
	protected:
		std::string	Type_;
	public:
		AAnimal();
		AAnimal(const std::string name);
		AAnimal(const AAnimal& copy);
		AAnimal& operator=(const AAnimal& copy_assign);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const = 0;
		virtual ~AAnimal(void);
};

#endif