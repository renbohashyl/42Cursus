#include "Cure.hpp"
#include <iostream>

Cure::Cure( void ) : AMateria("cure") { }

AMateria* Cure::clone() const {
	return (new Cure());
}

void	Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

Cure::~Cure( void ) { }