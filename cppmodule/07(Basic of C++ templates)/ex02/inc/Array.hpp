#pragma once

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>

template <typename T>
class Array {
	private:
		T	*data_;
		unsigned int m_size_;
	public:
		Array( void );
		Array( const unsigned int alloc_size );
		Array( const Array<T>& that );
		Array& operator= ( const Array<T>& rhs );
		T& operator[] ( const unsigned int index );
		const T& operator[] ( const unsigned int index ) const ;
		~Array();

		unsigned int size( void ) const ;

		class OutOfBound : public std::exception {
			public:
				const char * what() const throw() { return ("Out of Bound"); }
		};
		class AccessDenied : public std::exception {
			public:
				const char * what() const throw() { return ("Access Denied"); }
		};
};

#include "Array.tpp"

#endif