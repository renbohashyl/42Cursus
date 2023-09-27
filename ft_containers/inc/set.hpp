#ifndef __FT_SET_HPP__
# define __FT_SET_HPP__

#include "RBTree.hpp"

namespace ft
{

template <typename _Tp, typename _Compare = std::less<const _Tp>, typename _Alloc = std::allocator<const _Tp> >
class set
{
public:
	typedef _Tp			key_type;
	typedef _Tp			value_type;
	typedef _Compare 	key_compare;

	class value_compare
	 : public std::binary_function<value_type, value_type, bool> {
		friend class set<_Tp, _Compare, _Alloc>;
	protected:
		_Compare _M_comp;
		value_compare(_Compare __c) : _M_comp(__c) {}
	public:
		bool operator()(const value_type & __x, const value_type & __y) const {
			return _M_comp(__x, __y);
		}
	};

private:
	typedef RBTree<key_type, key_type, key_type, _Sel_Key_from_Tp<_Tp>, _Sel_Key_from_Tp<_Tp>, key_compare, _Alloc> _tree_type;
	typedef typename _tree_type::_Node_ptr _Node_ptr;
	_tree_type _M_tree;

public:
	typedef _Alloc	allocator_type;

	typedef typename allocator_type::const_reference	reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::const_pointer		pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	typedef typename _tree_type::const_iterator			iterator;
	typedef typename _tree_type::const_iterator			const_iterator;
	typedef typename _tree_type::const_reverse_iterator	reverse_iterator;
	typedef typename _tree_type::const_reverse_iterator	const_reverse_iterator;

	typedef typename _tree_type::size_type				size_type;
	typedef ptrdiff_t									differnce_type;

	explicit set(const _Compare & __comp = key_compare(), const allocator_type & __a = allocator_type())
		: _M_tree(__comp, __a) {}

	template <typename _InputIterator>
	set (_InputIterator __first, _InputIterator __last, const _Compare & __comp = key_compare(), const allocator_type & __a = allocator_type())
	 : _M_tree(__comp, __a) { insert(__first, __last); }

	set (const set & __x) : _M_tree(__x._M_tree) {}

	set<_Tp, _Compare, _Alloc> & operator= (const set<_Tp, _Compare, _Alloc> & __x) {
		_M_tree = __x._M_tree;
		return (*this);
	}

	key_compare key_comp() const { return (_M_tree.key_comp()); }
	value_compare value_comp() const { return (value_compare(_M_tree.key_comp())); }
	allocator_type get_allocator() const { return (_M_tree.get_allocator()); }

	void clear() { _M_tree.clear(); }
	void swap(set & __x) { _M_tree.swap(__x._M_tree); }

	iterator begin() { return (_M_tree.begin()); }
	const_iterator begin() const { return (_M_tree.begin()); }
	iterator end() { return (_M_tree.end()); }
	const_iterator end() const { return (_M_tree.end()); }
	reverse_iterator rbegin() { return (_M_tree.rbegin()); }
	const_reverse_iterator rbegin() const { return (_M_tree.rbegin()); }
	reverse_iterator rend() { return (_M_tree.rend()); }
	const_reverse_iterator rend() const { return (_M_tree.rend()); }

	size_type size() const { return (_M_tree.size()); }
	size_type max_size() const { return (_M_tree.max_size()); }

	pair<iterator,bool> insert (const value_type & val) {
		return(_M_tree.insert(val));
	}
	iterator insert (iterator position, const value_type & val) {
		typedef typename _tree_type::iterator _tree_iterator;
		return (iterator(_M_tree.iter_insert((_tree_iterator &)position, val)));
	}
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last) {
		while (first != last)
			_M_tree.insert(*(first++));
	}

	size_type erase (const key_type& key) { return (_M_tree.erase(key)); }
	void erase (iterator position) { _M_tree.erase(_M_tree._S_Key(*position)); }
	void erase (iterator first, iterator last) {
		while (first != last)
			erase(first++);
	}

	bool empty() const { return (_M_tree.empty()); }

	size_type count (const key_type& __key) const { return (_M_tree.iter_find(__key) != end()); }

	iterator find(const key_type & __key) { return (_M_tree.iter_find(__key)); }
	const_iterator find(const key_type & __key) const { return (_M_tree.iter_find(__key)); }

	iterator lower_bound(const key_type & __key) { return (_M_tree.lower_bound(__key)); }
	const_iterator lower_bound(const key_type & __key) const { return (_M_tree.lower_bound(__key)); }

	iterator upper_bound(const key_type & __key) { return (_M_tree.upper_bound(__key)); }
	const_iterator upper_bound(const key_type & __key) const { return (_M_tree.upper_bound(__key)); }

	pair<iterator, iterator> equal_range(const key_type & __key) {
		return (pair<iterator, iterator>(lower_bound(__key), upper_bound(__key)));
	}
	pair<const_iterator, const_iterator> equal_range(const key_type & __key) const {
		return (pair<const_iterator, const_iterator>(lower_bound(__key), upper_bound(__key)));
	}

	friend bool operator== (const set & __x, const set & __y) {
		return (__x._M_tree == __y._M_tree);
	}

	friend bool operator< (const set & __x, const set & __y) {
		return (__x._M_tree < __y._M_tree);
	}
};

template <typename _Tp, typename _Compare, typename _Alloc>
inline bool operator> (const set<_Tp, _Compare, _Alloc> & __x,
				const set<_Tp, _Compare, _Alloc> & __y) {
	return (__y < __x);
}

template <typename _Tp, typename _Compare, typename _Alloc>
inline bool operator<= (const set<_Tp, _Compare, _Alloc> & __x,
				const set<_Tp, _Compare, _Alloc> & __y) {
	return (!(__y < __x));
}

template <typename _Tp, typename _Compare, typename _Alloc>
inline bool operator>= (const set<_Tp, _Compare, _Alloc> & __x,
				const set<_Tp, _Compare, _Alloc> & __y) {
	return (!(__x < __y));
}

template <typename _Tp, typename _Compare, typename _Alloc>
inline bool operator!= (const set<_Tp, _Compare, _Alloc> & __x,
				const set<_Tp, _Compare, _Alloc> & __y) {
	return (!(__x == __y));
}

template <typename _Tp, typename _Compare, typename _Alloc>
void swap(const set<_Tp, _Compare, _Alloc> & __x,
		  const set<_Tp, _Compare, _Alloc> & __y) {
	__x.swap(__y);
}

}
#endif