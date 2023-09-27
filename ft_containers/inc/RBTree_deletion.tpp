/* ---------------------------------------- */
/* |                                      | */
/* |                utils                 | */
/* |                                      | */
/* ---------------------------------------- */

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::replace_node(_Node_ptr __x, _Node_ptr __y)
{
	if (_M_root() == __x)
		_M_root() = __y;
	else if (is_on_left(__x))
		__x->parent->left = __y;
	else
		__x->parent->right = __y;
	if (false == is_leaf(__y))
		__y->parent = __x->parent;
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::size_type \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase(const _Key & __key)
{
	_Node_ptr __next(_M_root());
	bool __is_leaf(is_leaf(__next));
	bool __comp(false);

	while (!(__is_leaf))
	{
		__comp = (_M_key_compare(__key, _S_Key(__next->value_field)));
		if (__comp)
			__next = __next->left;
		else if (__key == _S_Key(__next->value_field))
			break ;
		else
			__next = __next->right;
		__is_leaf = (is_leaf(__next));
	}
	if (!(__is_leaf)) {
		iterator step(__next);
		if (__next == _M_min_node())
			_M_min_node() = (++step)._M_node;
		else if (__next == _M_max_node())
			_M_max_node() = (--step)._M_node;
		erase_one_child(__next);
		--_node_count;
		return (1);
	}
	return (0);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase_one_child(_Node_ptr __x)
{
	_Node_ptr child(is_leaf(__x->right) ? __x->left : __x->right);

	if (false == is_leaf(__x->left) && false == is_leaf(__x->right))
	{
		_Node_ptr suc(getSuccessor(__x));

		replace_node(suc, is_leaf(suc->right) ? suc->left : suc->right);
		replace_node(__x, suc);
		suc->left = __x->left;
		suc->right = __x->right;
		if (!is_leaf(suc->left))
			suc->left->parent = suc;
		if (!is_leaf(suc->right))
			suc->right->parent = suc;
		__x->parent = _M_head;
		child = suc;
	}
	else
		replace_node(__x, child);
	if (__x->color == _RB_black) {
		if (false == is_leaf(child) && child->color == _RB_red)
			child->color = _RB_black;
		else
			erase_with_cases(child);
	}
	_M_delete_node(__x);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase_with_cases(_Node_ptr __x)
{
	if (is_leaf(__x) || __x->parent == _M_head)
		return ;
	
	_Node_ptr sibling(getSibling(__x));

	if (sibling->color == _RB_red)
	{
		__x->parent->color = _RB_red;
		sibling->color = _RB_black;
		if (is_on_left(__x))
			rotate_left(__x->parent);
		else
			rotate_right(__x->parent);
	}
	erase_case_second(__x);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase_case_second(_Node_ptr __x)
{
	_Node_ptr sibling(getSibling(__x));

	if (__x->parent->color == _RB_black && \
		sibling->color == _RB_black && \
		sibling->left->color == _RB_black && \
		sibling->right->color == _RB_black)
	{
		sibling->color = _RB_red;
		erase_with_cases(__x->parent);
		return ;
	}
	erase_case_third(__x);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase_case_third(_Node_ptr __x)
{
	_Node_ptr sibling(getSibling(__x));

	if (__x->parent->color == _RB_red && \
		sibling->color == _RB_black && \
		sibling->left->color == _RB_black && \
		sibling->right->color == _RB_black)
	{
		sibling->color = _RB_red;
		__x->parent->color = _RB_black;
		return ;
	}
	erase_case_fourth(__x);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase_case_fourth(_Node_ptr __x)
{
	_Node_ptr sibling(getSibling(__x));

	if (sibling->color != _RB_black)
		erase_case_fifth(__x);
	
	if (is_on_left(__x) && \
		sibling->right->color == _RB_black && \
		sibling->left->color == _RB_red)
	{
		sibling->color = _RB_red;
		sibling->left->color = _RB_black;
		rotate_right(sibling);
	}
	else if (!is_on_left(__x) && \
			sibling->left->color == _RB_black && \
			sibling->right->color == _RB_red)
	{
		sibling->color = _RB_red;
		sibling->right->color = _RB_black;
		rotate_left(__x);
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::erase_case_fifth(_Node_ptr __x)
{
	_Node_ptr sibling(getSibling(__x));

	sibling->color = __x->parent->color;
	__x->parent->color = _RB_black;

	if (is_on_left(__x)) {
		sibling->right->color = _RB_black;
		rotate_left(__x->parent);
	} else {
		sibling->left->color = _RB_black;
		rotate_right(__x->parent);
	}
}