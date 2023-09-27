#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria() { }
AMateria::AMateria(std::string const& type) : Type_(type) { }

std::string const& AMateria::getType() const {
	return (this->Type_);
}

void AMateria::use(ICharacter& target) {
	(void)target;
	std::cout << "Wrong Call" << std::endl;
}

AMateria::~AMateria(void) { }