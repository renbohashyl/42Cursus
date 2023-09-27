#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
	std::cout << "Dog : " << this->Type_ << " default constructor called" << std::endl;
}

Dog::Dog(const Dog& copy) : Animal("Dog") {
	(void)copy;
	std::cout << "Dog : " << this->Type_ << " copy constructor called" << std::endl;
}

const std::string& Dog::getType(void) const {
	return (this->Type_);
}

Dog& Dog::operator=(const Dog& operland) {
	std::cout << "Dog : " << this->Type_ << " copy_assignment_operator called" << std::endl;
	if (this != &operland) {
		this->Type_ = operland.Type_;
	}
	return (*this);
}

void	Dog::makeSound(void) const {
	std::cout << "BARK" << std::endl;
}

Dog::~Dog(void) {
	std::cout << "Dog : " << this->Type_ << " destructor called" << std::endl;
}