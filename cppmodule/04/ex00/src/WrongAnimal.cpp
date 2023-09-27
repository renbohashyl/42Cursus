#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal(void) : type("base WrongAnimal class") {
	std::cout << "the WrongAnimal : " << this->type << " has just been created" << std::endl;
}

WrongAnimal::WrongAnimal(std::string setName) : type(setName) {
	std::cout << "the WrongAnimal : " << this->type << " has just been created" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& copy) : type(copy.type) {
	std::cout << "the WrongAnimal : " << this->type << " has just been created" << std::endl;
}

const std::string& WrongAnimal::getType(void) const {
	return (this->type);
}

void	WrongAnimal::makeSound(void) const {
	std::cout << "wait, are you trying to \"WrongAnimal\" makes sound? that doesn't make sense " << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& copy_assign) {
	if (this != &copy_assign)
		this->type = copy_assign.type;
	return (*this);
}

WrongAnimal::~WrongAnimal() {
	std::cout << "the WrongAnimal : " << this->type << " has just been died" << std::endl;
}