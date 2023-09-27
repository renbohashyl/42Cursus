#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	private:
		Brain	*Brain_;
	public:
		Dog();
		Dog(const Dog& copy);
		Dog& operator=(const Dog& operland);
		const std::string& getType(void) const;
		void	makeSound(void) const;
		~Dog(void);
};