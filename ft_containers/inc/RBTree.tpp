template <typename _Tp>
const typename _RB_tree_node_base<_Tp>::_Self_ptr _RB_tree_node_base<_Tp>::leaf = NULL;

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::rotate_left(_Node_ptr __x)
{
	if (is_leaf(__x->right) || __x == _M_head)
		return ;

	_Node_ptr old__x_right = __x->right;
	_Node_ptr old__x_parent = __x->parent;

	if (old__x_parent == _M_head)
		old__x_parent = NULL;

	if (false == is_leaf(old__x_right->left))
		old__x_right->left->parent = __x;

	__x->right = old__x_right->left;
	__x->parent = old__x_right;
	old__x_right->left = __x;
	old__x_right->parent = old__x_parent;

	if (old__x_parent == NULL) {
		_M_root() = old__x_right;
		_M_root()->parent = _M_head;
	}
	else
	{
		if (old__x_parent->left == __x)
			old__x_parent->left = old__x_right;
		else
			old__x_parent->right = old__x_right;
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::rotate_right(_Node_ptr __x)
{
	if (is_leaf(__x->left) || __x == _M_head)
		return ;

	_Node_ptr old__x_left = __x->left;
	_Node_ptr old__x_parent = __x->parent;

	if (old__x_parent == _M_head)
		old__x_parent = NULL;

	if (false == is_leaf(old__x_left->right))
		old__x_left->right->parent = __x;

	__x->left = old__x_left->right;
	__x->parent = old__x_left;
	old__x_left->right = __x;
	old__x_left->parent = old__x_parent;

	if (old__x_parent == NULL) {
		_M_root() = old__x_left;
		_M_root()->parent = _M_head;
	}
	else
	{
		if (old__x_parent->right == __x)
			old__x_parent->right = old__x_left;
		else
			old__x_parent->left = old__x_left;
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr  \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::make_node\
(_Tp __value)
{
	_Node_ptr __temp(_M_make_node());
	try
	{
		_M_allocator.construct(&(__temp->value_field), __value);
		__temp->color = _RB_red;
		__temp->parent = _M_head;
		__temp->left = get_leaf();
		__temp->right = get_leaf();
		return (__temp);
	}
	catch(...)
	{
		_M_delete_node(__temp);
		throw ;
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::deleteTree(_Node_ptr __x)
{
	while (false == is_leaf(__x) && __x != NULL)
	{
		deleteTree(__x->right);
		_Node_ptr __temp = __x->left;
		if (false == is_leaf(__x))
			_M_delete_node(__x);
		__x = __temp;
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
bool RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::is_on_left(_Node_ptr & __x)
{
	if (is_leaf(__x) || is_leaf(__x->parent))
		return (false);
	else
		return (__x == __x->parent->left);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr  \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::getGrandParent(_Node_ptr & __x)
{
	if ((__x != NULL) && (__x->parent != NULL))
		return (__x->parent->parent);
	else
		return (NULL);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::getUncle(_Node_ptr & __x)
{
	_Node_ptr grand = this->getGrandParent(__x);

	if (is_leaf(grand))
		return (NULL);
	if (is_on_left(__x->parent))
		return (grand->right);
	else
		return (grand->left);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::getSibling(_Node_ptr & __x)
{
	if ((is_leaf(__x)) || (is_leaf(__x->parent)))
		return (NULL);
	if (is_on_left(__x))
		return (__x->parent->right);
	else
		return (__x->parent->left);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::getSuccessor(_Node_ptr & __x)
{
	_Node_ptr suc(__x->left);

	while(false == is_leaf(suc->right))
		suc = suc->right;
	
	return (suc);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_M_copy_node(_Node_ptr __x)
{
	_Node_ptr	__temp(make_node(__x->value_field));

	__temp->color = __x->color;
	__temp->left = get_leaf();
	__temp->right = get_leaf();
	return (__temp);
	
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_Node_ptr \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_M_copy(_Node_ptr __x, _Node_ptr __y)
{
	_Node_ptr	__top(_M_copy_node(__x));
	__top->parent = __y;

	try
	{
		if (__x->right)
			__top->right = _M_copy(__x->right, __top);
		__y = __top;
		__x = __x->left;

		while (false == is_leaf(__x))
		{
			_Node_ptr __temp(_M_copy_node(__x));

			__y->left = __temp;
			__temp->parent = __y;
			if (__x->right)
				__temp->right = _M_copy(__x->right, __temp);
			__y = __temp;
			__x = __x->left;
		}
	}
	catch (...)
	{
		deleteTree(__top);
		throw ;
	}

	return (__top);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::_M_initialize()
{
	_M_head->color = _RB_red;
	_M_head->parent = NULL;
	_M_head->left = _M_head;
	_M_head->right = _M_head;
}

/* ---------------------------------------- */
/* |                                      | */
/* |                public                | */
/* |                                      | */
/* ---------------------------------------- */

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::RBTree() : _Base(allocator_type()), _node_count(0), _M_key_compare()
{ _M_initialize(); }

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::RBTree(const _Compare & __comp)
: _Base(allocator_type()), _node_count(0), _M_key_compare(__comp)
{ _M_initialize(); }

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::RBTree(const _Compare & __comp, const allocator_type & __a)
: _Base(__a), _node_count(0), _M_key_compare(__comp)
{ _M_initialize(); }

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::RBTree(const RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator> & __copy)
: _Base(__copy.get_allocator()), _node_count(0), _M_key_compare(__copy._M_key_compare)
{
	if (__copy._M_root() == NULL)
		_M_initialize();
	else
	{
		_M_head->color = __copy._M_head->color;
		_M_root() = _M_copy(__copy._M_root(), _M_head);
		_M_min_node() = _RB_tree_node_base<_Tp>::_S_minimum(_M_root());
		_M_max_node() = _RB_tree_node_base<_Tp>::_S_maximum(_M_root());
	}
	_node_count = __copy._node_count;
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::clear()
{
	deleteTree(_M_root());
	_M_root() = NULL;
	_M_min_node() = _M_head;
	_M_max_node() = _M_head;
	_node_count = 0;
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::~RBTree()
{
	deleteTree(_M_root());
	_M_delete_node(_M_head);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::const_iterator \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iter_find(const _Key & __key) const
{
	_Node_ptr __next(_M_root());
	_Node_ptr __ret(_M_head);

	while (__next != NULL && !(is_leaf(__next)))
	{
		if (_M_key_compare(_S_Key(__next->value_field), __key))
			__next = __next->right;
		else {
			__ret = __next;
			__next = __next->left;
		}
	}
	iterator __check = iterator(__ret);
	if (__check == end() || _M_key_compare(__key, _S_Key(*__check)))
		return (end());
	return (__check);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iterator \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iter_find(const _Key & __key)
{
	_Node_ptr __next(_M_root());
	_Node_ptr __ret(_M_head);

	while (__next != NULL && !(is_leaf(__next)))
	{
		if (_M_key_compare(_S_Key(__next->value_field), __key))
			__next = __next->right;
		else {
			__ret = __next;
			__next = __next->left;
		}
	}
	iterator __check = iterator(__ret);
	if (__check == end() || _M_key_compare(__key, _S_Key(*__check)))
		return (end());
	return (__check);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iterator \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::lower_bound(const _Key & __key) const
{
	_Node_ptr __next(_M_root());
	_Node_ptr __ret(_M_head);

	while (__next != NULL && !(is_leaf(__next)))
	{
		if (_M_key_compare(_S_Key(__next->value_field), __key))
			__next = __next->right;
		else {
			__ret = __next;
			__next = __next->left;
		}
	}
	return (__ret);
}