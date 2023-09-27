#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public:
		WrongCat(void);
		WrongCat(std::string setName);
		WrongCat(const WrongCat& copy);
		WrongCat& operator=(const WrongCat& copy_assign);
		const std::string& getType(void) const;
		void	makeSound(void) const;
		~WrongCat(void);
};