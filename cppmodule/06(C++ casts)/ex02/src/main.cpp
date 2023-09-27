#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <exception>
#include <ctime>
#include <cstdlib>

void identify(Base *p) {
	if (dynamic_cast<A*>(p))
		std::cout << "p : A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "p : B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "p : C" << std::endl;
	else
		std::cout << "umm.... is it possible?" << std::endl;
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "p : A" << std::endl;
	}
	catch ( std::exception& e ) { }

	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "p : B" << std::endl;
	}
	catch ( std::exception& e ) { }

	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "p : C" << std::endl;
	}
	catch ( std::exception& e ) { }
}


Base *generate( void ) {
	srand(time(NULL));
	switch (int rand_num = rand() % 3)
	{
		case 0 :
			std::cout << "we made A class because random number was : " << rand_num % 3 << std::endl;
			return (new A);
		case 1 :
			std::cout << "we made B class because random number was : " << rand_num % 3 << std::endl;
			return (new B);
		default :
			std::cout << "we made C class because random number was : " << rand_num % 3 << std::endl;
			return (new C);
	}
}

int main() {
	Base *temp = generate();
	identify(temp);
	identify(*temp);
	return (0);
}