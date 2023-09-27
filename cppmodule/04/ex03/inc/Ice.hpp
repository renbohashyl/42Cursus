#include "AMateria.hpp"
#include "Character.hpp"

class Ice : public AMateria {
	private:
		Ice& operator=(const Ice& operland);
		Ice(const Ice& copy);
	public:
		Ice( void );
		AMateria *clone() const;
		void	use(ICharacter& target);
		~Ice( void );
};