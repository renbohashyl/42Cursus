#include "Span.hpp"

Span::Span( unsigned int n ) : vault_(n, 0), cursor_(0) { }

void Span::addNumber( const int nbr ) {
	if (this->cursor_ >= this->vault_.size())
		throw (Span::AlreadyFilled());
	this->vault_[(this->cursor_)++] = nbr;
}

void Span::fillNumber( const int nbr ) {
	std::fill( this->vault_.begin(), this->vault_.end(), nbr );
}

unsigned int Span::shortestSpan( void ) const {
	if (this->vault_.size() == 1)
		throw(Span::ThereIsOnlyOneNumber());
	else if (this->vault_.size() == 0)
		throw(Span::ThereAreNoStoredNumbers());

	std::vector<int> temp(this->vault_);
	int	min = __INT_MAX__;

	std::sort(temp.begin(), temp.end());

	if (temp.back() - temp.front() == 0)
		throw (Span::NoSpanCanBeFound());
	for (unsigned int i = 1; i < temp.size(); i++) {
		if (min > temp[i] - temp[i - 1])
			min = temp[i] - temp[i - 1];
	}
	return (min);
}

unsigned int	Span::longestSpan( void ) const {
	if (this->vault_.size() == 1)
		throw(Span::ThereIsOnlyOneNumber());
	else if (this->vault_.size() == 0)
		throw(Span::ThereAreNoStoredNumbers());

	std::vector<int> temp(this->vault_);

	std::sort(temp.begin(), temp.end());

	if (temp.back() - temp.front() == 0)
		throw (Span::NoSpanCanBeFound());

	return (temp.back() - temp.front());
}

unsigned int	Span::size( void ) const { return (this->vault_.size()) ; }

Span::~Span( ) { }