#include <iostream>
#include <exception>

// template <typename whatever, typename func>
// void iter(whatever * tArray, unsigned int size, func *f)
// {
// 	for (unsigned int i = 0; i < size; i++) {
// 		f(tArray[i]);
// 	}
// };

template <typename whatever>
void iter(whatever * tArray, unsigned int size, void (*f) ( whatever & ))
{
	for (unsigned int i = 0; i < size; i++) {
		f(tArray[i]);
	}
};

template <typename whatever>
void iter(const whatever * tArray, unsigned int size, void (*f) ( const whatever & ))
{
	for (unsigned int i = 0; i < size; i++) {
		f(tArray[i]);
	}
};

template <typename T>
void example(T & something) {
	something += something;
}

template <typename T>
void print(const T & something) {
	std::cout << something << std::endl;
}