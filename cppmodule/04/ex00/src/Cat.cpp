#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat") {
	std::cout << "Cat : " << this->Type_ << " default constructor called" << std::endl;
}

Cat::Cat(const Cat& copy) : Animal("Cat") {
	(void)copy;
	std::cout << "Cat : " << this->Type_ << " copy constructor called" << std::endl;
}

const std::string& Cat::getType(void) const {
	return (this->Type_);
}

Cat& Cat::operator=(const Cat& operland) {
	std::cout << "Cat : " << this->Type_ << " copy_assignment_operator called" << std::endl;
	if (this != &operland) {
		this->Type_ = operland.Type_;
	}
	return (*this);
}

void	Cat::makeSound(void) const {
	std::cout << "MEOW" << std::endl;
}

Cat::~Cat(void) {
	std::cout << "Cat : " << this->Type_ << " destructor called" << std::endl;
}