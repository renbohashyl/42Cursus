#include "AMateria.hpp"
#include "Character.hpp"

class Cure : public AMateria {
	private:
		Cure& operator=(const Cure& operland);
		Cure(const Cure& copy);
	public:
		Cure( void );
		AMateria *clone() const;
		void	use(ICharacter& target);
		~Cure( void );
};