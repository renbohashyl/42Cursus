#ifndef __FT_VECTOR_HPP__
# define __FT_VECTOR_HPP__

#include <memory>
#include <exception>
#include <algorithm>
#include "ft_iterator.hpp"
#include "ft_type_traits.hpp"
#include "ft_utility.hpp"

namespace ft
{

template <typename _Tp, typename _Allocator = std::allocator<_Tp> >
class __vector_alloc_base
{
public:
	typedef	_Allocator	allocator_type;
	allocator_type get_allocator() const { return _M_data_allocator; }

	__vector_alloc_base(const allocator_type& __a)
		: _M_data_allocator(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0) { }

protected:
	allocator_type	_M_data_allocator;
	_Tp* _M_start;
	_Tp* _M_finish;
	_Tp* _M_end_of_storage;

	_Tp*	_M_allocate(size_t __n) { return (_M_data_allocator.allocate(__n)); }
	void	_M_deallocate(_Tp* __p, size_t __n) {
		if (__p)
			_M_data_allocator.deallocate(__p, __n);
	}
};

template <typename _Tp, typename _Alloc>
class _vector_base : public __vector_alloc_base<_Tp, _Alloc>
{
protected:
	typedef __vector_alloc_base<_Tp, _Alloc>		_Base;
	typedef typename _Base::allocator_type			allocator_type;

	using _Base::_M_start;
	using _Base::_M_finish;
	using _Base::_M_end_of_storage;
	using _Base::_M_allocate;
	using _Base::_M_deallocate;
	using _Base::_M_data_allocator;

public:
	_vector_base(const allocator_type& __a) : _Base(__a) {}
	_vector_base(size_t __n, const allocator_type& __a) : _Base(__a) {
		_M_start = _M_allocate(__n);
		_M_finish = _M_start;
		_M_end_of_storage = _M_start + __n;
	}

	~_vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }
};

template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
class vector : protected _vector_base<_Tp, _Alloc>
{
public:
	typedef _vector_base<_Tp, _Alloc> _Base;
	typedef _Tp					value_type;
	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;
	typedef value_type*			iterator;
	typedef const value_type*	const_iterator;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef vector<_Tp, _Alloc>	_Self;

	typedef typename _Base::allocator_type		allocator_type;
	typedef reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef reverse_iterator<iterator>			reverse_iterator;

private:
	using _Base::_M_start;
	using _Base::_M_finish;
	using _Base::_M_end_of_storage;
	using _Base::_M_allocate;
	using _Base::_M_data_allocator;

	template <typename _InputIterator>
	void alloc_destroy(_InputIterator __first, _InputIterator __last) {
		while (__first != __last)
			_M_data_allocator.destroy(++__first);
		if (__last != _M_finish)
			_M_data_allocator.destroy(__last);
	}

protected:
	template <typename _Iterator>
	iterator _M_allocate_and_copy(size_type __n, _Iterator __first, _Iterator __last);

	iterator insert(iterator __position);
	void _M_insert_aux_module(iterator __position, const _Tp& __x);
	void _M_insert_aux(iterator __position, const _Tp& __x);
	void _M_insert_aux(iterator __position);

	template <typename _InputIterator>
	void _M_range_insert(iterator __pos, _InputIterator __first, _InputIterator __last);

	template <typename _Integer>
	void _M_initialize_aux(_Integer __n, _Integer __Tpue);
	template <typename _InputIterator>
	void _M_range_initialize(_InputIterator __first, _InputIterator __last);

	template <typename _InputIter>
	void _M_assign_aux(_InputIter __first, _InputIter __last);

public:
	allocator_type get_allocator() const { return _M_data_allocator; }

	iterator begin() { return (_M_start); }
	const_iterator begin() const { return (_M_start); }
	iterator end() { return (_M_finish); }
	const_iterator end() const { return (_M_finish); }

	reverse_iterator rbegin() { return (reverse_iterator(_M_finish)); }
	reverse_iterator rend() { return (reverse_iterator(_M_start)); }

	reference front() { return *(begin()); }
	const_reference front() const { return *(begin()); }
	reference back() { return *(end() - 1); }
	const_reference back() const { return *(end() - 1); }
	reference at (size_type __n) {
		if (__n > size())
			throw (std::out_of_range("ERROR : OUT_OF_RANGE"));
		return (*(begin() + __n));
	}
	const_reference at (size_type __n) const {
		if (__n > size())
			throw (std::out_of_range("ERROR : OUT_OF_RANGE"));
		return (*(begin() + __n));
	}

	size_type size() const { return (size_type(end() - begin())); }
	size_type max_size() const { return (size_type(-1) / sizeof(_Tp)); }
	size_type capacity() const { return (size_type(_M_end_of_storage - begin())); }
	bool empty() const { return (begin() == end()); }

	reference operator[] (size_type __n) { return *(begin() + __n); }
	const_reference operator[] (size_type __n) const { return *(begin() + __n); }
	vector<_Tp, _Alloc> & operator=(const vector<_Tp, _Alloc> & __x);

	void reserve(size_type __n)
	{
		//if the __n <= capacity(), do nothing.
		//it means the size of allocated memory is greater than or equal to __n
		if (__n > capacity())
		{
			const size_type __old_size(size());
			iterator __temp(_M_allocate_and_copy(__n, _M_start, _M_finish));

			alloc_destroy(_M_start, _M_finish);
			this->_M_deallocate(_M_start, _M_end_of_storage - _M_start);
			_M_start = __temp;
			_M_finish = __temp + __old_size;
			_M_end_of_storage = _M_start + __n;
		}
	}

	void assign(size_t __n, const value_type& __Tp) {
		//if __n is greater than capacity, reallocation is faster
		//__n is less than capacity, but greater than size, just fill with __Tp and expand the iterator
		//__n is less than whatever, do like initialize
		if (__n > capacity()) {
			vector<_Tp, _Alloc> __tmp(__n, __Tp, get_allocator());
			__tmp.swap(*this);
		}
		else if (__n > size()) {
			std::fill(begin(), end(), __Tp);
			std::uninitialized_fill_n(_M_finish, __n - size(), __Tp);
			_M_finish = _M_finish + (__n - size());
			_M_end_of_storage = _M_finish;
		}
		else {
			std::fill_n(begin(), __n, __Tp);
			erase(begin() + __n, end());
		}
	}
	template <typename _InputIterator>
	void assign(_InputIterator __first, _InputIterator __last, typename enable_if<is_integral<_InputIterator>::value>::itisnt* = 0) {
		_M_assign_aux(__first, __last);
	}

	void push_back(const _Tp& __x) {
		if (_M_finish != _M_end_of_storage) {
			_M_data_allocator.construct(_M_finish, __x);
			++_M_finish;
		}
		else
			_M_insert_aux(end(), __x);
	}

	void pop_back() {
		//_M_finish is pointing end of iterator(beyond the last_value such as the NULL of char * in C)
		//so need to be point last_value and call destructor
		--_M_finish;
		_M_data_allocator.destroy(_M_finish);
	}

	iterator erase(iterator __position) {
		//here is the exmaple.
		//if this contianer has 1 2 3 4 5, and input __position is begin() + 2,
		//then __position is pointing 3
		//1. after std::copy, this container will have 1 2 4 5 5
		//2. after pop_back, this container will have 1 2 4 5
		if (__position + 1 != end())
			std::copy(__position + 1, _M_finish, __position);
		--_M_finish;
		_M_data_allocator.destroy(_M_finish);
		return (__position);
	}
	template <typename _InputIterator>
	iterator erase(_InputIterator __first, _InputIterator __last) {
		iterator __i = std::copy(__last, _M_finish, __first);
		alloc_destroy(__i, _M_finish);
		_M_finish = _M_finish - (__last - __first);
		return (__first);
	}

	void resize(size_type __new_size, const _Tp& __x) {
		if (__new_size < size())
			erase(begin() + __new_size, end());
		else
			insert(end(), __new_size - size(), __x);
	}
	void resize(size_type __new_size) { resize(__new_size, _Tp()); }
	void clear() { erase(begin(), end()); }

	void swap(_Self& __x) {
		std::swap(_M_start, __x._M_start);
		std::swap(_M_finish, __x._M_finish);
		std::swap(_M_end_of_storage, __x._M_end_of_storage);
	}

	iterator insert(iterator __position, const _Tp& __x) {
		size_type __n = __position - begin();
		if (_M_finish != _M_end_of_storage && __position == end()) {
			_M_data_allocator.construct(_M_finish, __x);
			++_M_finish;
		}
		else 
			_M_insert_aux(__position, __x);
		return (begin() + __n);
	}

	void insert (iterator __position, size_type __n, const _Tp& __x) {
		if (__n != 0) {
			if (size_type(_M_end_of_storage - _M_finish) >= __n)
			{
				_Tp __x_copy = __x;
				const size_type __elems_after = _M_finish - __position;
				iterator __old_finish = _M_finish;
				if (__elems_after > __n) {
					std::uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
					_M_finish += __n;
					std::copy_backward(__position, __old_finish - __n, __old_finish);
					std::fill(__position, __position + __n, __x_copy);
				}
				else {
					std::uninitialized_fill_n(_M_finish, __n - __elems_after, __x_copy);
					_M_finish += __n - __elems_after;
					std::uninitialized_copy(__position, __old_finish, _M_finish);
					_M_finish += __elems_after;
					std::fill(__position, __old_finish, __x_copy);
				}
			}
			else {
				const size_type __old_size = size();
				const size_type __len = __old_size + (__old_size > __n ? __old_size : __n);
					//construct is not suitable for range allocation
				iterator __new_start = _M_allocate(__len);
				iterator __new_finish = __new_start;

				try {
					__new_finish = std::uninitialized_copy(_M_start, __position, __new_start);
					std::uninitialized_fill_n(__new_finish, __n, __x);
					__new_finish += __n;
					__new_finish = std::uninitialized_copy(__position, _M_finish, __new_finish);
				}
				catch(...) {
					alloc_destroy(__new_start, __new_finish);
					this->_M_deallocate(__new_start, __len);
				}
				alloc_destroy(_M_start, _M_finish);
				this->_M_deallocate(_M_start, _M_end_of_storage - _M_start);
				_M_start = __new_start;
				_M_finish = __new_finish;
				_M_end_of_storage = __new_start + __len;
			}
		}
	}
	template <typename _InputIterator>
	void insert(iterator __pos, _InputIterator __first, _InputIterator __last, typename enable_if<is_integral<_InputIterator>::value>::itisnt* = 0) {
		_M_range_insert(__pos, __first, __last);
	}

	explicit vector (const allocator_type& __a = allocator_type()) : _Base(__a) { } // default constructor

	vector (size_type __n, const value_type& __Tpue = value_type(), const allocator_type& __a = allocator_type())
	 : _Base(__n, __a)
	{
		std::uninitialized_fill_n(_M_start, __n, __Tpue);
		_M_finish = _M_start + __n;
	} // __n = alloc size, _Tpue = initialization value

	template <typename _Integer>
	vector(_Integer __n, _Integer __Tpue, const allocator_type& __a = allocator_type(), typename enable_if<is_integral<_Integer>::value>::type* = 0)
	: _Base(__a) {
		_M_initialize_aux(__n, __Tpue);
	} // range_fill contructor

	template <typename _InputIterator>
	vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a = allocator_type(), typename enable_if<is_integral<_InputIterator>::value>::itisnt* = 0)
	: _Base(__a) {
		_M_range_initialize(__first, __last);
	}

	vector(const _Self& __x) : _Base(__x.size(), __x.get_allocator()) {
		_M_finish = std::uninitialized_copy(__x.begin(), __x.end(), _M_start);
	} // copy constructor

	~vector() { alloc_destroy(_M_start, _M_finish); }

};

#include "vector.tpp"

}

#endif