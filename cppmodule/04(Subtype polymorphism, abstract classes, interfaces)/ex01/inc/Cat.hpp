#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
	private:
		Brain	*Brain_;
	public:
		Cat();
		Cat(const Cat& copy);
		Cat& operator=(const Cat& operland);
		const std::string& getType(void) const;
		void	makeSound(void) const;
		~Cat(void);
};