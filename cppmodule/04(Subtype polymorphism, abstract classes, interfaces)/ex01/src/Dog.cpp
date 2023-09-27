#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
	std::cout << "Dog : " << this->getType() << " default constructor called" << std::endl;
	this->Brain_ = new Brain;
}

Dog::Dog(const Dog& copy) : Animal(copy.Type_) {
	std::cout << "Dog : " << this->getType() << " copy constructor called" << std::endl;
	this->Brain_ = new Brain(*(copy.Brain_));
}

const std::string& Dog::getType(void) const {
	return (this->Type_);
}

Dog& Dog::operator=(const Dog& operland) {
	std::cout << "Dog : " << this->getType() << " copy_assignment_operator called" << std::endl;
	if (this != &operland) {
		this->Type_ = operland.Type_;
		Dog	tempOperland(operland);

		if (this->Brain_) {
			Brain *tmp;

			tmp = this->Brain_;
			this->Brain_ = tempOperland.Brain_;
			tempOperland.Brain_ = tmp;
		}
	}
	return (*this);
}

void	Dog::makeSound(void) const {
	std::cout << "BARK" << std::endl;
}

Dog::~Dog(void) {
	delete Brain_;
	std::cout << "Dog : " << this->getType() << " destructor called" << std::endl;
}