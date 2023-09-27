#include "AAnimal.hpp"
#include <iostream>

AAnimal::AAnimal() : Type_("Base AAnimal") {
	std::cout << "the AAnimal : " << this->getType() << " default constructor called" << std::endl;
}

AAnimal::AAnimal(const std::string name) : Type_(name) {
	std::cout << "the AAnimal : " << this->getType() << " default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& copy) : Type_(copy.Type_) {
	std::cout << "the AAnimal : " << this->getType() << " copy constructor called" << std::endl;
}

const std::string& AAnimal::getType(void) const {
	return (this->Type_);
}

AAnimal& AAnimal::operator=(const AAnimal& copy_assign) {
	if (this != &copy_assign)
		this->Type_ = copy_assign.Type_;
	return (*this);
}

AAnimal::~AAnimal() {
	std::cout << "the AAnimal : " << this->getType() << " destructor called" << std::endl;
}