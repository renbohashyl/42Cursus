template <typename _Tp>
struct _RB_tree_iterator_base
{
	typedef _RB_tree_node_base<_Tp> *		_Node_ptr;
	typedef _RB_tree_node_base<_Tp>			_S_Base;
	typedef bidirectional_iterator_tag		iterator_category;
	typedef ptrdiff_t						difference_type;

	_Node_ptr _M_node;

	void _M_increase()
	{
		if (false == _S_Base::_is_leaf(_M_node->right))
		{
			_M_node = _M_node->right;
			while (false == _S_Base::_is_leaf(_M_node->left))
				_M_node = _M_node->left;
		}
		else
		{
			_Node_ptr __y(_M_node->parent);
			while (_M_node == __y->right)
			{
				_M_node = __y;
				__y = __y->parent;
			}
			if (_M_node->right != __y)
				_M_node = __y;
		}
	}

	void _M_decrease()
	{
		if (_M_node->color == _RB_red && _M_node->parent->parent == _M_node)
			_M_node = _M_node->right;
		else if (false == _S_Base::_is_leaf(_M_node->left))
		{
			_Node_ptr __y = _M_node->left;
			while (false == _S_Base::_is_leaf(__y->right))
				__y = __y->right;
			_M_node = __y;
		}
		else
		{
			_Node_ptr __y(_M_node->parent);
			while (__y && _M_node == __y->left)
			{
				_M_node = __y;
				__y = __y->parent;
			}
			_M_node = __y;
		}
	}
};

template <typename _Tp, typename _Ref, typename _Ptr>
struct _RB_tree_iterator : public _RB_tree_iterator_base<_Tp>
{
	typedef _Tp		value_type;
	typedef _Ref	reference;
	typedef _Ptr	pointer;

	typedef _RB_tree_iterator<_Tp, _Tp&, _Tp*> iterator;
	typedef _RB_tree_iterator<_Tp, const _Tp&, const _Tp*> const_iterator;
	typedef _RB_tree_iterator<_Tp, _Ref, _Ptr> _Self;

	typedef _RB_tree_node_base<_Tp> * _Node_ptr;
	typedef typename _RB_tree_iterator_base<_Tp>::iterator_category iterator_category;

	using _RB_tree_iterator_base<_Tp>::_M_node;
	using _RB_tree_iterator_base<_Tp>::_M_increase;
	using _RB_tree_iterator_base<_Tp>::_M_decrease;

	_RB_tree_iterator() {}
	_RB_tree_iterator(_Node_ptr __x) { _M_node = __x; }
	_RB_tree_iterator(const iterator & __it) { _M_node = __it._M_node; }

	reference operator * () const { return (_M_node->value_field); }
	pointer operator -> () const { return (&(operator*())); }

	_Self & operator ++ ()
	{
		_M_increase();
		return (*this);
	}
	_Self operator ++ (int)
	{
		_Self __temp(*this);
		_M_increase();
		return (__temp);
	}
	_Self & operator -- ()
	{
		_M_decrease();
		return (*this);
	}
	_Self operator -- (int)
	{
		_Self __temp(*this);
		_M_decrease();
		return (__temp);
	}
};

template <typename _Tp, typename _Ref, typename _Ptr>
inline bool operator== (const _RB_tree_iterator<_Tp, _Ref, _Ptr>& __x,
						const _RB_tree_iterator<_Tp, _Ref, _Ptr>& __y)
{ return (__x._M_node == __y._M_node); }

template<typename _Tp>
inline bool operator== (const _RB_tree_iterator<_Tp, const _Tp&, const _Tp*>& __x,
						const _RB_tree_iterator<_Tp, _Tp&, _Tp*>& __y)
{ return (__x._M_node == __y._M_node); }

template<typename _Tp>
inline bool operator== (const _RB_tree_iterator<_Tp, _Tp&, _Tp*>& __x,
						const _RB_tree_iterator<_Tp, const _Tp&, const _Tp*>& __y)
{ return (__x._M_node == __y._M_node); }

template <typename _Tp, typename _Ref, typename _Ptr>
inline bool operator!= (const _RB_tree_iterator<_Tp, _Ref, _Ptr>& __x,
						const _RB_tree_iterator<_Tp, _Ref, _Ptr>& __y)
{ return (__x._M_node != __y._M_node); }

template<typename _Tp>
inline bool operator!= (const _RB_tree_iterator<_Tp, const _Tp&, const _Tp*>& __x,
						const _RB_tree_iterator<_Tp, _Tp&, _Tp*>& __y)
{ return (__x._M_node != __y._M_node); }

template<typename _Tp>
inline bool operator!= (const _RB_tree_iterator<_Tp, _Tp&, _Tp*>& __x,
						const _RB_tree_iterator<_Tp, const _Tp&, const _Tp*>& __y)
{ return (__x._M_node != __y._M_node); }