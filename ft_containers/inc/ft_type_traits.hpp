#ifndef __FT_TYPE_TRAITS_HPP__
# define __FT_TYPE_TRAITS_HPP__
/*
	the integral types (from cplusplus)
	-----------------------------
	| bool						|
	| char						|
	| wchar_t					|
	| signed char				|
	| short int					|
	| int						|
	| long int					|
	| long long int				|
	| unsigned char				|
	| unsigned short int		|
	| unsigned int				|
	| unsigned long int			|
	| unsigned long long int	|
	| char16_t(c++11)			|
	| char32_t(c++11)			|
	-----------------------------
*/

#include "ft_iterator.hpp"

namespace ft
{

template <typename _Val> struct is_integral { static const bool value = false; };
template <> struct is_integral<bool> { static const bool value = true; };
template <> struct is_integral<char> { static const bool value = true; };
template <> struct is_integral<wchar_t> { static const bool value = true; };
template <> struct is_integral<signed char> { static const bool value = true; };
template <> struct is_integral<short int> { static const bool value = true; };
template <> struct is_integral<int> { static const bool value = true; };
template <> struct is_integral<long int> { static const bool value = true; };
template <> struct is_integral<long long int> { static const bool value = true; };
template <> struct is_integral<unsigned char> { static const bool value = true; };
template <> struct is_integral<unsigned short int> { static const bool value = true; };
template <> struct is_integral<unsigned int> { static const bool value = true; };
template <> struct is_integral<unsigned long int> { static const bool value = true; };
template <> struct is_integral<unsigned long long int> { static const bool value = true; };

//bacause char16_t and char32_t is not defined in C++98 standard
#ifdef char16_t
template <> struct is_integral<char16_t> { static const bool value = true; };
#endif

#ifdef char32_t
template <> struct is_integral<char32_t> { static const bool value = true; };
#endif

}

#endif