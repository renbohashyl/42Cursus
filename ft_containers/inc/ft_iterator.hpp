#ifndef __FT_ITERATOR_HPP__
# define __FT_ITERATOR_HPP__

#include <cstddef>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename _Tp, typename _Distance> struct input_iterator {
  typedef input_iterator_tag	iterator_category;
  typedef _Tp					value_type;
  typedef _Distance				difference_type;
  typedef _Tp*					pointer;
  typedef _Tp&					reference;
};

struct output_iterator {
  typedef output_iterator_tag	iterator_category;
  typedef void					value_type;
  typedef void					difference_type;
  typedef void					pointer;
  typedef void					reference;
};

template <typename _Tp, typename _Distance> struct forward_iterator {
  typedef forward_iterator_tag	iterator_category;
  typedef _Tp					value_type;
  typedef _Distance				difference_type;
  typedef _Tp*					pointer;
  typedef _Tp&					reference;
};


template <typename _Tp, typename _Distance> struct bidirectional_iterator {
  typedef bidirectional_iterator_tag	iterator_category;
  typedef _Tp							value_type;
  typedef _Distance						difference_type;
  typedef _Tp*							pointer;
  typedef _Tp&							reference;
};

template <typename _Tp, typename _Distance> struct random_access_iterator {
  typedef random_access_iterator_tag	iterator_category;
  typedef _Tp							value_type;
  typedef _Distance						difference_type;
  typedef _Tp*							pointer;
  typedef _Tp&							reference;
};

template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
		  typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator {
	typedef _Category	iterator_category;
	typedef _Tp			value_type;
	typedef _Distance	difference_type;
	typedef _Pointer	pointer;
	typedef _Reference	reference;
};

template <typename _Iterator>
struct iterator_traits {
	typedef typename _Iterator::iterator_category	iterator_category;
	typedef typename _Iterator::value_type			value_type;
	typedef typename _Iterator::difference_type		difference_type;
	typedef typename _Iterator::pointer				pointer;
	typedef typename _Iterator::reference			reference;
};

template <typename _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag	iterator_category;
  typedef _Tp							value_type;
  typedef ptrdiff_t						difference_type;
  typedef _Tp*							pointer;
  typedef _Tp&							reference;
};

template <typename _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag	iterator_category;
  typedef _Tp							value_type;
  typedef ptrdiff_t						difference_type;
  typedef const _Tp*					pointer;
  typedef const _Tp&					reference;
};

template <typename _Tp, typename _Distance> 
inline input_iterator_tag iterator_category(const input_iterator<_Tp, _Distance>&)
  { return input_iterator_tag(); }

inline output_iterator_tag iterator_category(const output_iterator&)
  { return output_iterator_tag(); }

template <typename _Tp, typename _Distance> 
inline forward_iterator_tag iterator_category(const forward_iterator<_Tp, _Distance>&)
  { return forward_iterator_tag(); }

template <typename _Tp, typename _Distance> 
inline bidirectional_iterator_tag iterator_category(const bidirectional_iterator<_Tp, _Distance>&)
  { return bidirectional_iterator_tag(); }

template <typename _Tp, typename _Distance> 
inline random_access_iterator_tag iterator_category(const random_access_iterator<_Tp, _Distance>&)
  { return random_access_iterator_tag(); }

template <typename _Tp>
inline random_access_iterator_tag iterator_category(const _Tp*)
  { return random_access_iterator_tag(); }

template <typename _Tp, typename _Distance> 
inline _Tp* value_type(const input_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <typename _Tp, typename _Distance> 
inline _Tp* value_type(const forward_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <typename _Tp, typename _Distance> 
inline _Tp* value_type(const bidirectional_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <typename _Tp, typename _Distance> 
inline _Tp* value_type(const random_access_iterator<_Tp, _Distance>&)
  { return (_Tp*)(0); }

template <typename _Tp>
inline _Tp* value_type(const _Tp*) { return (_Tp*)(0); }

template <typename _Tp, typename _Distance> 
inline _Distance* distance_type(const input_iterator<_Tp, _Distance>&)
  { return (_Distance*)(0); }

template <typename _Tp, typename _Distance> 
inline _Distance* distance_type(const forward_iterator<_Tp, _Distance>&)
  { return (_Distance*)(0); }

template <typename _Tp, typename _Distance> 
inline _Distance* 
distance_type(const bidirectional_iterator<_Tp, _Distance>&)
  { return (_Distance*)(0); }

template <typename _Tp, typename _Distance> 
inline _Distance* 
distance_type(const random_access_iterator<_Tp, _Distance>&)
  { return (_Distance*)(0); }

#define __FT_ITERATOR_CATEGORY(__i)	iterator_category(__i)
#define __FT_DISTANCE_TYPE(__i)		distance_type(__i)
#define __FT_TpUE_TYPE(__i)		value_type(__i)


template <typename _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
__distance(_InputIterator __first, _InputIterator __last, input_iterator_tag)
{
  typename iterator_traits<_InputIterator>::difference_type __n = 0;
  while (__first != __last) {
    ++__first;
	++__n;
  }
  return (__n);
}

template <typename _RandomAccessIterator>
inline typename iterator_traits<_RandomAccessIterator>::difference_type
__distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
		  random_access_iterator_tag)
  { return (__last - __first); }

template <typename _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
distance(_InputIterator __first, _InputIterator __last) {
  typedef typename iterator_traits<_InputIterator>::iterator_category _Category;
  return __distance(__first, __last, _Category());
}

template <typename _Iterator>
class	reverse_iterator {
	protected:
		_Iterator current;
	public:
		typedef typename iterator_traits<_Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<_Iterator>::value_type			value_type;
		typedef typename iterator_traits<_Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<_Iterator>::pointer			pointer;
		typedef typename iterator_traits<_Iterator>::reference			reference;

		typedef _Iterator iterator_type;
		typedef reverse_iterator<_Iterator> _Self;

		reverse_iterator() { }
		explicit reverse_iterator(iterator_type __x) : current(__x) { }

		reverse_iterator(const _Self& __x) : current(__x.current) { }

		template <typename _Iter>
		reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) { }

		iterator_type base() const { return (current); }
		reference operator*() const {
			_Iterator __temp = current;
			return *(--__temp);
		}
		pointer	operator->() const { return (&(operator*())); }
		_Self& operator++() {
			--current;
			return (*this);
		}
		_Self operator++(int) {
			_Self __temp(*this);
			--current;
			return (__temp);
		}
		_Self& operator--() {
			++current;
			return (*this);
		}
		_Self operator--(int) {
			_Self __temp(*this);
			++current;
			return (__temp);
		}
		_Self operator+ (difference_type __n) const {
			return _Self(current - __n);
		}
		_Self& operator+= (difference_type __n) {
			current -= __n;
			return (*this);
		}
		_Self operator- (difference_type __n) const {
			return _Self(current + __n);
		}
		_Self& operator-= (difference_type __n) {
			current += __n;
			return (*this);
		}
		reference operator[] (difference_type __n) const { return *(*this + __n); }

		template <typename _Iter>
		bool operator==(const reverse_iterator<_Iter>& __y) const { return (this->base() == __y.base()); }
		bool operator==(const reverse_iterator<_Iterator>& __y) const { return (this->base() == __y.base()); }

		template <typename _Iter>
		bool operator!=(const reverse_iterator<_Iter>& __y) const { return (!(operator==(__y))); }
		bool operator!=(const reverse_iterator<_Iterator>& __y) const { return (!(operator==(__y))); }

		template <typename _Iter>
		bool operator<(const reverse_iterator<_Iter>& __y) const { return (this->base() > __y.base()); }
		bool operator<(const reverse_iterator<_Iterator>& __y) const { return (this->base() > __y.base()); }

		template <typename _Iter>
		bool operator<=(const reverse_iterator<_Iter>& __y) const { return (operator<(__y) || operator==(__y)); }
		bool operator<=(const reverse_iterator<_Iterator>& __y) const { return (operator<(__y) || operator==(__y)); }

		template <typename _Iter>
		bool operator>(const reverse_iterator<_Iter>& __y) const { return (this->base() < __y.base()); }
		bool operator>(const reverse_iterator<_Iterator>& __y) const { return (this->base() < __y.base()); }

		template <typename _Iter>
		bool operator>=(const reverse_iterator<_Iter>& __y) const { return (operator>(__y) || operator==(__y)); }
		bool operator>=(const reverse_iterator<_Iterator>& __y) const { return (operator>(__y) || operator==(__y)); }

		typename reverse_iterator<_Iterator>::difference_type operator- \
		 (const reverse_iterator<_Iterator>& __y) {
			return (__y.base() - this->base());
		}
		reverse_iterator<_Iterator> operator+ \
		 (typename reverse_iterator<_Iterator>::difference_type __n) {
			return (reverse_iterator<_Iterator>(this->base() - __n));
		}
};

template <typename _Iterator>
inline reverse_iterator<_Iterator>
operator+(typename reverse_iterator<_Iterator>::difference_type __n,
		  const reverse_iterator<_Iterator>& __x) {
	return (reverse_iterator<_Iterator>(__x.base() - __n));
}

}

#endif