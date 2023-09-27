#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	std::cout << "Brain : default constructor called" << std::endl;
}

Brain::Brain(const Brain& copy) {
	for (int i = 0; i < MAX_IDEAS; i++)
		this->Ideas_[i] = copy.Ideas_[i];
	std::cout << "Brain : copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& operland) {
	if (this != &operland) {
		for (int i = 0; i < MAX_IDEAS; i++)
			this->Ideas_[i] = operland.Ideas_[i];
	}
	std::cout << "Brain : copy_assignment_operator called" << std::endl;
	return (*this);
}

Brain::~Brain() {
	std::cout << "Brain : destructor called" << std::endl;
}