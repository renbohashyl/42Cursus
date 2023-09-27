#include <iostream>
#include "Span.hpp"

int main() {
	Span span(5);
	int	asdf(3);

	try {
		span.addNumber(1);
		span.addNumber(10);
		span.addNumber(asdf);
		span.addNumber(22);
		span.addNumber(6667);
		std::cout << span.shortestSpan() << std::endl;
		std::cout << span.longestSpan() << std::endl;
		span.addNumber(6667323);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
}