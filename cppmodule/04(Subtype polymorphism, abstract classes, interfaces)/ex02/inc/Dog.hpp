#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
	private:
		Brain	*Brain_;
	public:
		Dog();
		Dog(const Dog& copy);
		Dog& operator=(const Dog& operland);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const;
		~Dog(void);
};