#pragma once

#ifndef __EASYFIND_HPP__
# define __EASYFIND_HPP__

#include <iterator>
#include <exception>

template <typename T>
typename T::iterator easyfind( T & haystack, int needle );

template <typename T>
const typename T::iterator easyfind( const T & haystack, const int needle );

#include "easyfind.tpp"

#endif