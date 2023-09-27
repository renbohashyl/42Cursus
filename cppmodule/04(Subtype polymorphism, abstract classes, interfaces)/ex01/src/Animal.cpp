#include "Animal.hpp"
#include <iostream>

Animal::Animal() : Type_("Base Animal") {
	std::cout << "the ANIMAL : " << this->getType() << " default constructor called" << std::endl;
}

Animal::Animal(const std::string name) : Type_(name) {
	std::cout << "the ANIMAL : " << this->getType() << " default constructor called" << std::endl;
}

Animal::Animal(const Animal& copy) : Type_(copy.Type_) {
	std::cout << "the ANIMAL : " << this->getType() << " copy constructor called" << std::endl;
}

const std::string& Animal::getType(void) const {
	return (this->Type_);
}

void	Animal::makeSound(void) const {
	std::cout << "wait, are you trying to \"ANIMAL\" makes sound? that doesn't make sense " << std::endl;
}

Animal& Animal::operator=(const Animal& copy_assign) {
	if (this != &copy_assign)
		this->Type_ = copy_assign.Type_;
	return (*this);
}

Animal::~Animal() {
	std::cout << "the ANIMAL : " << this->getType() << " destructor called" << std::endl;
}