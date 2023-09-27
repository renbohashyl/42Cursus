#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
	private:
		AMateria	*Srcs_[4];
		MateriaSource(const MateriaSource& copy);
		MateriaSource& operator=(const MateriaSource& operland);
	public:
		MateriaSource();
		void	learnMateria(AMateria* src);
		AMateria*	createMateria(std::string const& type);
		~MateriaSource();
};