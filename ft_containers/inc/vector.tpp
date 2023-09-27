/* ---------------------------------------- */
/* |                                      | */
/* |              protected               | */
/* |                                      | */
/* ---------------------------------------- */

/* ---------------------------------------- */
/* |                 alloc                | */
/* ---------------------------------------- */
template <typename _Val, typename _Alloc>
template <typename _Iterator>
typename vector<_Val, _Alloc>::iterator vector<_Val, _Alloc>::_M_allocate_and_copy \
  (size_type __n, _Iterator __first, _Iterator __last)
{
	iterator __result = this->_M_allocate(__n);
	try {
		std::uninitialized_copy(__first, __last, __result);
		return (__result);
	}
	catch (...) {
		this->_M_deallocate(__result, __n);
		throw ;
	}
}

/* ---------------------------------------- */
/* |                insert                | */
/* ---------------------------------------- */
template <typename _Val, typename _Alloc>
template <typename _InputIterator>
void vector<_Val, _Alloc>::_M_range_insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
	for (; __first != __last; ++__first) {
		__pos = insert(__pos, *(__first));
		++__pos;
	}
}
template <typename _Val, typename _Alloc>
typename vector<_Val, _Alloc>::iterator vector<_Val, _Alloc>::insert(typename vector<_Val, _Alloc>::iterator __position) {
	size_type __n = __position - begin();
	if (_M_finish != _M_end_of_storage && __position == end()) {
		_M_data_allocator.construct(_M_finish);
		++_M_finish;
	}
	else
		_M_insert_aux(__position);
	return (begin() + __n);
}

template <typename _Val, typename _Alloc>
void vector<_Val, _Alloc>::_M_insert_aux_module(iterator __position, const _Val& __x)
{
	const size_type __old_size = size();
	const size_type __len = (__old_size != 0 ? __old_size << 1 : 1);

	iterator	__new_start = this->_M_allocate(__len);
	iterator	__new_finish = __new_start;
	try {
		__new_finish = std::uninitialized_copy(_M_start, __position, __new_start);
		_M_data_allocator.construct(__new_finish, __x);
		++__new_finish;
		__new_finish = std::uninitialized_copy(__position, _M_finish, __new_finish);
	}
	catch (...) {
		alloc_destroy(__new_start, __new_finish);
		this->_M_deallocate(__new_start, __len);
	}
	if (!empty())
		alloc_destroy(begin(), end());
	this->_M_deallocate(_M_start, _M_end_of_storage - _M_start);
	_M_start = __new_start;
	_M_finish = __new_finish;
	_M_end_of_storage = __new_start + __len;
}

template <typename _Val, typename _Alloc>
void vector<_Val, _Alloc>::_M_insert_aux(iterator __position)
{
	if (_M_finish != _M_end_of_storage) {
		_M_data_allocator.construct(_M_finish, *(_M_finish - 1));
		++_M_finish;
		std::copy_backward(__position, _M_finish -2, _M_finish - 1);
		*__position = _Val();
	}
	else {
		_M_insert_aux_module(__position, (_Val&)0);
	}
}
template <typename _Val, typename _Alloc>
void vector<_Val, _Alloc>::_M_insert_aux(iterator __position, const _Val& __x)
{
	if (_M_finish != _M_end_of_storage) {
		_M_data_allocator.construct(_M_finish, *(_M_finish - 1));
		++_M_finish;
		_Val __x_copy(__x);
		std::copy_backward(__position, _M_finish -2, _M_finish - 1);
		*__position = __x_copy;
	}
	else {
		_M_insert_aux_module(__position, __x);
	}
}

/* ---------------------------------------- */
/* |               initialize             | */
/* ---------------------------------------- */
template <typename _Val, typename _Alloc>
template <typename _Integer>
void vector<_Val, _Alloc>::_M_initialize_aux(_Integer __n, _Integer __value) {
	_M_start = _M_allocate(__n);
	_M_end_of_storage = _M_start + __n;

	//according to cplusplus, std::uninitialized_fill_n has no return( = return type is void) in C++98
	//so, _M_finish will be (moved '_M_start' as much as '__n')

	std::uninitialized_fill_n(_M_start, __n, __value);
	_M_finish = _M_start + __n;
}

template <typename _Val, typename _Alloc>
template <typename _InputIterator>
void vector<_Val, _Alloc>::_M_range_initialize(_InputIterator __first, _InputIterator __last) {
	for (; __first != __last; ++__first)
		push_back(*__first);
}

/* ---------------------------------------- */
/* |                 assign               | */
/* ---------------------------------------- */

template <typename _Val, typename _Alloc>
template <typename _InputIter>
void vector<_Val, _Alloc>::_M_assign_aux(_InputIter __first, _InputIter __last) {
	iterator __cur = begin();

	for (; __first != __last && __cur != end(); ++__cur, ++__first)
		*__cur = *__first;

	//if the size() is greather than (__last - __first)
		//need to be clear(deallocate) the rest of them
	//if the size() is less than or equal to (__last - __first)
		//need to allocate and insert them
	if (__first == __last)
		erase(__cur, end());
	else
		insert(end(), __first, __last);
}

/* ---------------------------------------- */
/* |                                      | */
/* |                public                | */
/* |                                      | */
/* ---------------------------------------- */

template <typename _Val, typename _Alloc>
vector<_Val, _Alloc>& vector<_Val, _Alloc>::operator=(const vector<_Val, _Alloc>& __x) {
	if (&__x == this)
		return (*this);

	const size_type __xlen = __x.size();

	if (__xlen > this->capacity()) {
		iterator __tmp = this->_M_allocate_and_copy(__xlen, __x.begin(), __x.end());
		this->alloc_destroy(_M_start, _M_finish);
		this->_M_deallocate(_M_start, _M_end_of_storage - _M_start);
		_M_start = __tmp;
		_M_end_of_storage = _M_start + __xlen;
	}
	else if (this->size() >= __xlen) {
		iterator __i = std::copy(__x.begin(), __x.end(), this->begin());
		this->alloc_destroy(__i, _M_finish);
	}
	else {
		std::copy(__x.begin(), __x.begin() + this->size(), _M_start);
		std::uninitialized_copy(__x.begin() + this->size(), __x.end(), _M_finish);
	}
	_M_finish = _M_start + __xlen;
	return (*this);
}

template <class _Val, class Alloc>
inline bool operator== (const vector<_Val, Alloc>& __x, const vector<_Val, Alloc>& __y) {
	return (__x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin()));
}
template <class _Val, class Alloc>
inline bool operator!= (const vector<_Val, Alloc>& __x, const vector<_Val, Alloc>& __y) {
	return (!(operator==(__x, __y)));
}
template <class _Val, class Alloc>
inline bool operator<  (const vector<_Val, Alloc>& __x, const vector<_Val, Alloc>& __y) {
	return (lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()));
}

template <class _Val, class Alloc>
inline bool operator<= (const vector<_Val, Alloc>& __x, const vector<_Val, Alloc>& __y) {
	return (!(operator>(__x, __y)));
}

template <class _Val, class Alloc>
inline bool operator>  (const vector<_Val, Alloc>& __x, const vector<_Val, Alloc>& __y) {
	return (lexicographical_compare(__y.begin(), __y.end(), __x.begin(), __x.end()));
}

template <class _Val, class Alloc>
inline bool operator>= (const vector<_Val, Alloc>& __x, const vector<_Val, Alloc>& __y) {
	return (!(operator<(__x, __y)));
}
