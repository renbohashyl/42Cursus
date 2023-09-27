#include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog();
		Dog(const Dog& copy);
		Dog& operator=(const Dog& copy_assign);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const;
		~Dog(void);
};