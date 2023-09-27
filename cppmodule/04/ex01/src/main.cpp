#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

void	do_test_second(void)
{
	std::cout << "\n==============Here comes a new test==============" << std::endl;
	Animal *(arr[10]);

	for (int i = 0; i < 10; i++)
		(i % 2) ? arr[i] = new Dog() : arr[i] = new Cat();
	std::cout << "\n--------------Creation complete--------------\n" << std::endl;
	for (int i = 0; i < 10; i++)
		delete arr[i];
	std::cout << "\n--------------delete complete--------------\n" << std::endl;
	std::cout << "================new test finished================\n" << std::endl;
}

void	do_test_first(void)
{
	std::cout << "\n==============Here comes a new test==============" << std::endl;
	Animal *meta = new Dog();
	std::cout << std::endl;
	Animal *temp = new Dog();
	std::cout << std::endl;
	Animal *temp2;
	temp2 = new Cat();
	Animal *temp3;
	temp3 = new Cat();

	*temp2 = *temp3;
	*meta = *temp;
	std::cout << std::endl;
	delete meta;
	std::cout << std::endl;
	delete temp;
	std::cout << std::endl;
	delete temp2;
	std::cout << std::endl;
	delete temp3;
	std::cout << "================new test finished================\n" << std::endl;
}

void	do_test_basic(void)
{
	const Animal* j = new Dog();
	std::cout << std::endl;
	const Animal* i = new Cat();
	std::cout << std::endl;

	delete i;
	std::cout << std::endl;
	delete j;
	std::cout << std::endl;
}

void	it_must_be_error(void)
{
	//because WrongCat did shallow
	std::cout << "\n\n===========WrongAnimals will do===========" << std::endl << std::endl;
	WrongCat	*wCat = new WrongCat();
	WrongCat	*wCat_tmp = new WrongCat();

	wCat = wCat_tmp;
	delete wCat_tmp;
	delete wCat;
}

int main()
{
	do_test_basic();
	//do_test_first();
	//do_test_second();
	//it_must_be_error();
	system("leaks Idon’twanttosettheworldonfire");

	return (0);
}