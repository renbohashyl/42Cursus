#pragma once

#ifndef __SPAN_HPP__
# define __SPAN_HPP__

#include <vector>
#include <iterator>
#include <exception>
#include <iostream>

class Span {
	private:
		std::vector<int> vault_;
		unsigned int	cursor_;
		Span( void );
		Span(const Span & rhs);
		Span & operator= (const Span & operland);
	public:
		Span( unsigned int n );
		~Span();

		void addNumber( const int nbr );
		void fillNumber ( const int nbr );

		unsigned int shortestSpan( void ) const ;
		unsigned int longestSpan( void ) const ;
		unsigned int size( void ) const ;

		class ThereAreNoStoredNumbers : public std::exception {
			public:
				const char * what() const throw() { return ("There are no stored numbers"); }
		};
		class ThereIsOnlyOneNumber : public std::exception {
			public:
				const char * what() const throw() { return ("There is only one number"); }
		};
		class NoSpanCanBeFound : public std::exception {
			public:
				const char * what() const throw() { return ("No Span Can Be Found"); }
		};
		class AlreadyFilled : public std::exception {
			public:
				const char * what() const throw() { return ("Already all field is filled :)"); }
		};
};

#endif