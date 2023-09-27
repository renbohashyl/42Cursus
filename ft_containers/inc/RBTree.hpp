#ifndef __RB_TREE_HPP__
# define __RB_TREE_HPP__

#include <memory>
#include <exception>
#include <algorithm>
#include <functional>
#include "ft_iterator.hpp"
#include "ft_utility.hpp"

namespace ft
{

enum _RB_color { _RB_red = false, _RB_black = true };

template <typename _Tp>
struct _RB_tree_node_base
{
	typedef struct _RB_tree_node_base<_Tp> _Self;
	typedef struct _RB_tree_node_base<_Tp> * _Self_ptr;

	_Tp value_field;
	_RB_color color;

	_Self_ptr parent;
	_Self_ptr left;
	_Self_ptr right;

	static const _Self_ptr leaf;

	_RB_tree_node_base()
	 : color(_RB_red), parent(NULL), left(NULL), right(NULL) { }

	static _Self_ptr _get_leaf() { return (_RB_tree_node_base<_Tp>::leaf); }
	static bool _is_leaf(_Self_ptr & __x) { return (__x == _Self::_get_leaf()); }

	static _Self_ptr _S_minimum(_Self_ptr __x)
	{
		while (!(_Self::_is_leaf(__x->left)) && __x->left != NULL)
			__x = __x->left;
		return (__x);
	}
	static _Self_ptr _S_maximum(_Self_ptr __x)
	{
		while (!(_Self::_is_leaf(__x->right)) && __x->right != NULL)
			__x = __x->right;
		return (__x);
	}

};

template <typename _Tp, typename _Allocator, typename _Node_Allocator = std::allocator<_RB_tree_node_base<_Tp> > >
struct _RB_tree_node : public _RB_tree_node_base<_Tp>
{
	typedef _Allocator allocator_type;
	allocator_type get_allocator() const { return (_M_allocator); }
	_RB_tree_node(const allocator_type & __a)
		: _M_head(_M_make_node()), _M_allocator(__a), _M_node_allocator(_Node_Allocator()) { }

protected:
	typedef _RB_tree_node_base<_Tp> _Base;
	typedef _RB_tree_node_base<_Tp> * _Node_ptr;

	_Node_ptr _M_head;
	allocator_type _M_allocator;
	_Node_Allocator _M_node_allocator;

	_Node_ptr _M_make_node() { return (_M_node_allocator.allocate(1)); }
	void _M_delete_node(_Node_ptr __p) { return (_M_node_allocator.deallocate(__p, 1)); }
};

#include "RBTree_iterator.tpp"

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
struct RBTree : public _RB_tree_node<_Tp, _Allocator>
{
	typedef _RB_tree_node<_Tp, _Allocator> _Base;
	typedef _RB_tree_node_base<_Tp> * _Node_ptr;
	typedef const _RB_tree_node_base<_Tp> * const_Node_ptr;
	typedef _RB_tree_node_base<_Tp> _S_base;
	typedef size_t size_type;

	typedef _RB_tree_iterator<_Tp, _Tp &, _Tp *> iterator;
	typedef _RB_tree_iterator<_Tp, const _Tp &, const _Tp *> const_iterator;

	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;

	typedef typename _Base::allocator_type allocator_type;
	allocator_type get_allocator() const { return (_Base::get_allocator()); }

	RBTree();
	RBTree(const _Compare & __comp);
	RBTree(const _Compare & __comp, const allocator_type & __a);
	RBTree(const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __copy);
	~RBTree();

	RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & operator= \
	(const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __x)
	{
		if (this != &__x)
		{
			clear();
			_node_count = 0;
			_M_key_compare = __x._M_key_compare;
			if (__x._M_root() == NULL)
			{
				_M_root() = NULL;
				_M_min_node() = NULL;
				_M_max_node() = NULL;
			}
			else
			{
				_M_head->color = __x._M_head->color;
				_M_root() = _M_copy(__x._M_root(), _M_head);
				_M_min_node() = _RB_tree_node_base<_Tp>::_S_minimum(_M_root());
				_M_max_node() = _RB_tree_node_base<_Tp>::_S_maximum(_M_root());
			}
			_node_count = __x._node_count;
		}
		return (*this);
	}

	size_type	_node_count;
	_Compare	_M_key_compare;

	using _Base::_M_head;
	using _Base::_M_make_node;
	using _Base::_M_delete_node;
	using _Base::_M_allocator;
	using _Base::_M_node_allocator;

	static const _Key & _S_Key (const _Tp & __x) { return (_Sel_Key()(__x)); }
	static _Value & _S_Val (_Tp & __x) { return (_Sel_Val()(__x)); }

	_Node_ptr & _M_root() const { return (_M_head->parent); }
	_Node_ptr & _M_min_node() const { return (_M_head->left); }
	_Node_ptr & _M_max_node() const { return (_M_head->right); }
	_Node_ptr _M_copy(_Node_ptr __x, _Node_ptr __y);
	_Node_ptr _M_copy_node(_Node_ptr __x);

	//utils_for_behavior_of_rb_tree
	void _M_initialize();
	void clear();
	void deleteTree(_Node_ptr __x);
	void rotate_left(_Node_ptr  __x);
	void rotate_right(_Node_ptr  __x);

	_Node_ptr make_node(_Tp __value);
	_Node_ptr getGrandParent(_Node_ptr & __x);
	_Node_ptr getUncle(_Node_ptr & __x);
	_Node_ptr getSibling(_Node_ptr & __x);
	_Node_ptr getSuccessor(_Node_ptr & __x);
	_Node_ptr get_leaf() const { return (_S_base::_get_leaf()); }

	bool is_on_left(_Node_ptr & __x);
	bool is_leaf(_Node_ptr & __x) const { return(_S_base::_is_leaf(__x)); }

	//insertion
	void insertion_crack_check(_Node_ptr  __x);
	void fix_case_first(_Node_ptr  __x);
	void fix_case_second(_Node_ptr  __x);
	void fix_case_third(_Node_ptr  __x);

	//deletion
	void replace_node(_Node_ptr __x, _Node_ptr __y);
	void erase_one_child(_Node_ptr __x);
	void erase_with_cases(_Node_ptr __x);
	void erase_case_second(_Node_ptr __x);
	void erase_case_third(_Node_ptr __x);
	void erase_case_fourth(_Node_ptr __x);
	void erase_case_fifth(_Node_ptr __x);

	//accessor
	_Compare key_comp() const { return (_M_key_compare); }
	iterator begin() { return (_M_min_node()); }
	const_iterator begin() const { return (_M_min_node()); }
	iterator end() { return (_M_head); }
	const_iterator end() const { return (_M_head); }
	reverse_iterator rbegin() { return (reverse_iterator(end())); }
	const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
	reverse_iterator rend() { return (reverse_iterator(begin())); }
	const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }
	bool empty() const { return (_node_count == 0); }
	size_type size() const { return (_node_count); }
	size_type max_size() const { return (size_type(-1) / sizeof(_S_base)); }

	void swap(RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __swap)
	{
		std::swap(_M_head, __swap._M_head);
		std::swap(_node_count, __swap._node_count);
		std::swap(_M_key_compare, __swap._M_key_compare);
	}

	iterator iter_find (const _Key & __key);
	const_iterator iter_find (const _Key & __key) const ;

	iterator iter_insert_aux(_Node_ptr __less, _Node_ptr __more, const _Tp & __value);
	iterator iter_insert(iterator __position, const _Tp & __value);
	pair<iterator, bool> insert(_Tp __value);

	size_type erase(const _Key & __key);

	iterator lower_bound(const _Key & __key) const ;
	iterator upper_bound(const _Key & __key) const {
		iterator ret = lower_bound(__key);

		if (__key == _S_Key(*ret))
			++ret;
		return (ret);
	}
};
template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
inline bool operator== (const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __x,
						const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __y)
{
	return (__x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin()));
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
inline bool operator< (const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __x,
						const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __y)
{
	return (lexicographical_compare(__x.begin(), __x.end() , __y.begin(), __y.end()));
}


#include "RBTree.tpp"
#include "RBTree_insertion.tpp"
#include "RBTree_deletion.tpp"

}

#endif