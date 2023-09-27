#include "Cat.hpp"
#include <iostream>

Cat::Cat() : AAnimal("Cat") {
	std::cout << "Cat : " << this->getType() << " default constructor called" << std::endl;
	this->Brain_ = new Brain;
}

Cat::Cat(const Cat& copy) : AAnimal(copy.Type_) {
	std::cout << "Cat : " << this->getType() << " copy constructor called" << std::endl;
	this->Brain_ = new Brain(*(copy.Brain_));
}

const std::string& Cat::getType(void) const {
	return (this->Type_);
}

Cat& Cat::operator=(const Cat& operland) {
	std::cout << "Cat : " << this->getType() << " copy_assignment_operator called" << std::endl;
	if (this != &operland) {
		this->Type_ = operland.Type_;
		delete this->Brain_;
		this->Brain_ = new Brain(*(operland.Brain_));
	}
	return (*this);
}

void	Cat::makeSound(void) const {
	std::cout << "MEOW" << std::endl;
}

Cat::~Cat(void) {
	delete Brain_;
	std::cout << "Cat : " << this->getType() << " destructor called" << std::endl;
}