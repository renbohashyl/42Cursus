#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat(void) : WrongAnimal("WrongCat") {
	std::cout << "WrongCat : " << this->type << " has just been born with Brain!" << std::endl;
	this->brain = new Brain;
}

WrongCat::WrongCat(const std::string setName) : WrongAnimal(setName) {
	std::cout << "WrongCat : " << this->type << " has just been born with Brain!" << std::endl;
	this->brain = new Brain;
}

WrongCat::WrongCat(const WrongCat& copy) : WrongAnimal(copy.type) {
	std::cout << "WrongCat : " << this->type << " has just been copied!" << std::endl;
	this->brain = new Brain(*(copy.brain));
}

const std::string& WrongCat::getType(void) const {
	return (this->type);
}

WrongCat& WrongCat::operator=(const WrongCat& operland) {
	std::cout << "WrongCat : " << this->type << " copy_assignment_operator called" << std::endl;
	if (this != &operland) {
		this->type = operland.type;
		this->brain = operland.brain;
	}
	return (*this);
}

void	WrongCat::makeSound(void) const {
	std::cout << "MEOW" << std::endl;
}

WrongCat::~WrongCat(void) {
	delete brain;
	std::cout << "WrongCat : " << this->type << " has just been died" << std::endl;
}