#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main() {
	std::cout << "==============Animals will do==============" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete i;
	delete j;
	delete meta;

	std::cout << "==============WrongAnimals will do==============" << std::endl;
	const WrongAnimal* wanim = new WrongAnimal();
	const WrongAnimal* wcat = new WrongCat();

	wanim->makeSound();
	wcat->makeSound();

	delete wanim;
	delete wcat;

	return (0);
}