#ifndef __FT_UTILITY_HPP__
# define __FT_UTILITY_HPP__

namespace ft
{

/* ---------------------------------------- */
/* |                                      | */
/* |              enable_if               | */
/* |                                      | */
/* ---------------------------------------- */

template <bool, typename _Val = void> struct enable_if {typedef _Val itisnt;};
template <typename _Val> struct enable_if<true, _Val> {typedef _Val type;};

/* ---------------------------------------- */
/* |                                      | */
/* |               compare                | */
/* |                                      | */
/* ---------------------------------------- */

template <typename InputIterator1, typename InputIterator2>
bool equal \
 (InputIterator1 __first1, InputIterator1 __last1, InputIterator2 __first2)
{
	while (__first1 != __last1)
	{
		if (*__first1 != *__first2)
			return (false);
		++__first1;
		++__first2;
	}
	return (true);
}

template <typename InputIterator1, typename InputIterator2, typename eq_compare>
bool equal \
 (InputIterator1 __first1, InputIterator1 __last1, InputIterator2 __first2, eq_compare __eq)
{
	while (__first1 != __last1)
	{
		if (__eq(*__first1, *__first2))
			return (false);
		++__first1;
		++__first2;
	}
	return (true);
}

template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare \
 (InputIterator1 __first1, InputIterator1 __last1, InputIterator2 __first2, InputIterator2 __last2)
{
	for (; __first2 != __last2; ++__first1, ++__first2)
	{
		if (__first1 == __last1 || *__first1 < *__first2)
			return (true);
		else if (*__first2 < *__first1)
			return (false);
	}
	return (false);
}

template <typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare \
 (InputIterator1 __first1, InputIterator1 __last1, InputIterator2 __first2, InputIterator2 __last2, Compare __comp)
{
	for (; __first2 != __last2; ++__first1, ++__first2)
	{
		if (__first1 == __last1 || __comp(*__first1, *__first2))
			return (true);
		else if (__comp(*__first2, *__first1))
			return (false);
	}
	return (false);
}

template <typename _Pair>
struct _Sel_Key_from_pair {
	const typename _Pair::first_type& operator()(const _Pair & __x) const { return __x.first; }
};

template <typename _Pair>
struct _Sel_Val_from_pair {
	typename _Pair::second_type& operator()(_Pair & __x) { return __x.second; }
};

template <typename _Tp>
struct _Sel_Key_from_Tp {
	const _Tp & operator()(const _Tp & __x) const { return (__x); }
};

/* ---------------------------------------- */
/* |                                      | */
/* |                 pair                 | */
/* |                                      | */
/* ---------------------------------------- */

template <typename _T1, typename _T2>
class pair
{
public:
	typedef _T1 first_type;
	typedef _T2 second_type;

	_T1	first;
	_T2	second;

	pair() : first(_T1()), second(_T2()) { }
	pair(const _T1& __x, const _T2& __y) : first(__x), second(__y) { }

	template <typename _U1, typename _U2>
	pair(const pair<_U1, _U2>& __copy) : first(__copy.first), second(__copy.second) {}

	pair<_T1, _T2> & operator=(pair<_T1, _T2> const& __p) {
		first = __p.first;
		second = __p.second;
		return (*this);
	}
};

template <typename _T1, typename _T2>
inline bool operator== (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return (__x.first == __y.first && \
			__x.second == __y.second);
}

template <typename _T1, typename _T2>
inline bool operator!= (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return (!operator==(__x, __y));
}

template <typename _T1, typename _T2>
inline bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return (__x.first < __y.first || 
			(!(__y.first < __x.first) && __x.second < __y.second));
}

template <typename _T1, typename _T2>
inline bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return (operator<(__y, __x));
}

template <typename _T1, typename _T2>
inline bool operator<= (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return (!(operator<(__y, __x)));
}

template <typename _T1, typename _T2>
inline bool operator>= (const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return (!(operator<(__x, __y)));
}

template <typename _T1, typename _T2>
pair<_T1, _T2> make_pair (_T1 __x, _T2 __y) {
	return (pair<_T1, _T2>(__x, __y));
}

}
#endif