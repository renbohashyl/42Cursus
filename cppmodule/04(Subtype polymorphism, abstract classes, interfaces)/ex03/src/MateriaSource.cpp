#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; i++)
		(this->Srcs_)[i] = NULL;
}

void	MateriaSource::learnMateria(AMateria* src) {
	for (int i = 0; i < 4; i++) {
		if ((this->Srcs_)[i] == NULL) {
			this->Srcs_[i] = src;
			break ;
		}
	}
}

AMateria*	MateriaSource::createMateria(std::string const& type) {
	for (int i = 0; i < 4; i++) {
		if (this->Srcs_[i] && type == (this->Srcs_)[i]->getType())
			return ((this->Srcs_)[i]->clone());
	}
	return (NULL);
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < 4; i++) {
		if (this->Srcs_[i]) {
			delete ((this->Srcs_)[i]);
			this->Srcs_[i] = NULL;
		}
	}
}
