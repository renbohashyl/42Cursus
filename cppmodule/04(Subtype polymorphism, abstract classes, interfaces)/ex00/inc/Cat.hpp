#include "Animal.hpp"

class Cat : public Animal {
	public:
		Cat();
		Cat(const Cat& copy);
		Cat& operator=(const Cat& copy_assign);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const;
		~Cat(void);
};