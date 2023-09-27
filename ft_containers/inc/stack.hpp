#ifndef __FT_STACK_HPP__
# define __FT_STACK_HPP__

#include "vector.hpp"

namespace ft
{

template <typename _Tp, typename _Underlying = vector<_Tp> >
class stack
{
protected:
	_Underlying c;
	typedef	typename _Underlying::reference			reference;
	typedef	typename _Underlying::const_reference	const_reference;
public:
	typedef	typename _Underlying::value_type		value_type;
	typedef	typename _Underlying::size_type			size_type;
	typedef	_Underlying								container_type;

	stack() : c() { }
	explicit stack(const _Underlying & __cp) : c(__cp) { }

	bool empty() const { return (c.empty()); }
	size_type size() const { return (c.size()); }
	reference top() { return (c.back()); }
	const_reference top() const { return (c.back()); }

	void push(const value_type & __x) { c.push_back(__x); }
	void pop() { c.pop_back(); }

	friend bool operator== (const stack & __x, const stack & __y) {
		return (__x.c == __y.c);
	}

	friend bool operator< (const stack & __x, const stack & __y) {
		return (__x.c < __y.c);
	}
};

template <typename _Tp, typename _Underlying>
bool operator!= (const stack<_Tp, _Underlying>& __x, const stack<_Tp, _Underlying>& __y) {
	return (!(__x == __y));
}

template <typename _Tp, typename _Underlying>
bool operator<= (const stack<_Tp, _Underlying>& __x, const stack<_Tp, _Underlying>& __y) {
	return (!(__x > __y));
}

template <typename _Tp, typename _Underlying>
bool operator>  (const stack<_Tp, _Underlying>& __x, const stack<_Tp, _Underlying>& __y) {
	return (__y < __x);
}

template <typename _Tp, typename _Underlying>
bool operator>= (const stack<_Tp, _Underlying>& __x, const stack<_Tp, _Underlying>& __y) {
	return (!(__x < __y));
}


}
#endif