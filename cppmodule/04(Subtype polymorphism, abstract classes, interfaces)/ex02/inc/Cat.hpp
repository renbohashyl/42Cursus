#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
	private:
		Brain	*Brain_;
	public:
		Cat();
		Cat(const Cat& copy);
		Cat& operator=(const Cat& operland);
		const std::string& getType(void) const;
		virtual void	makeSound(void) const;
		~Cat(void);
};