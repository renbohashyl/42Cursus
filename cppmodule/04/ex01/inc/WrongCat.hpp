#include "WrongAnimal.hpp"
#include "Brain.hpp"

class WrongCat : public WrongAnimal {
	private:
		Brain	*brain;
	public:
		WrongCat(void);
		WrongCat(const std::string setName);
		WrongCat(const WrongCat& copy);
		WrongCat& operator=(const WrongCat& operland);
		const std::string& getType(void) const;
		void	makeSound(void) const;
		~WrongCat(void);
};