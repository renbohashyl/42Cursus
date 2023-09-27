template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iterator \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iter_insert_aux\
(_Node_ptr __less, _Node_ptr __more, const _Tp & __value)
{
	_Node_ptr temp;

	if (__more == _M_head || __less != NULL || _M_key_compare(_S_Key(__value), _S_Key(__more->value_field)))
	{
		//__more이 end()거나 __less에 값이 들어있거나 __value의 키값이 __more보다 작다면
		temp = make_node(__value);
		__more->left = temp;
		if (__more == _M_head)
		{
			_M_root() = temp;
			_M_max_node() = temp;
		}
		else if (__more == _M_min_node())
			_M_min_node() = temp;
	}
	else
	{
		temp = make_node(__value);
		__more->right = temp;
		if (__more == _M_max_node())
			_M_max_node() = temp;
	}
	temp->parent = __more;
	temp->left = NULL;
	temp->right = NULL;
	insertion_crack_check(_M_max_node());
	++(_node_count);
	return (temp);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iterator \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iter_insert(iterator __position, const _Tp & __value)
{
	if (__position == begin())
	{
		if (_node_count > 0 && _M_key_compare(_S_Key(__value), _S_Key(*__position)))
			return (iter_insert_aux(__position._M_node, __position._M_node, __value));
		else
			return ((insert(__value)).first);
	}
	else if (__position == end())
	{
		if (_M_key_compare(_S_Key(_M_max_node()->value_field), _S_Key(__value)))
			return (iter_insert_aux(0, _M_max_node(), __value));
		else
			return ((insert(__value)).first);
	}
	else
	{
		//양 끝이 아닐 때
		iterator __before = __position;
		--(__before);
		if (_M_key_compare(_S_Key(*__before), _S_Key(__value)) && _M_key_compare(_S_Key(__value), _S_Key(*__position)))
		{
			//before < __value < position 일 때, 즉 position을 효율적으로 이용할 수 있을 때
			if (is_leaf(__before._M_node->right))
				return (iter_insert_aux(0, __before._M_node, __value));
			else
				return (iter_insert_aux(__position._M_node, __position._M_node, __value));
		}
		else //position을 효율적으로 사용하지 못할 때
			return ((insert(__value)).first);
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
pair <typename RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::iterator, bool> \
RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::insert(_Tp __value)
{
	_Node_ptr temp(make_node(__value));

	if (_M_root() == NULL) {
		temp->color = _RB_black;
		_M_root() = temp;
		_M_min_node() = temp;
		_M_max_node() = temp;
		_node_count++;
		return (pair<iterator, bool>(iterator(temp), true));
	}

	_Node_ptr __next(_M_root());
	bool __comp(false);

	while (false == is_leaf(__next) && __next != NULL)
	{
		__comp = (_M_key_compare(_S_Key(__value), _S_Key(__next->value_field)));
		temp->parent = __next;
		if (__comp)
			__next = __next->left;
		else if (_S_Key(__value) == _S_Key(__next->value_field)) {
			_M_delete_node(temp);
			return (pair<iterator, bool>(iterator(__next), false));
		}
		else
			__next = __next->right;
	}
	if (__comp)
		temp->parent->left = temp;
	else
		temp->parent->right = temp;

	insertion_crack_check(temp);
	_node_count++;

	if (_M_key_compare(_S_Key(__value), _S_Key(_M_min_node()->value_field)))
		_M_min_node() = temp;
	if (_M_key_compare(_S_Key(_M_max_node()->value_field), _S_Key(__value)))
		_M_max_node() = temp;
	return (pair<iterator, bool>(iterator(temp), true));
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::insertion_crack_check(_Node_ptr __x)
{
	//삽입 후 룰 위반의 경우가 있는지 확인
	//규칙 1. 루트노트는 항상 검은색노드여야함
	if (__x == _M_root())
		__x->color = _RB_black;
	else
		fix_case_first(__x);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::fix_case_first(_Node_ptr __x)
{
	//규칙 2. 레드노드는 연달아 나타날 수 없다. == 레드노드의 양쪽 자식 전부는 블랙노드여야 한다.
	//새로 삽입된 노드는 무조건 레드노드임. 그러므로 블랙->레드->블랙->레드는 문제가 없음
	if (__x->parent->color == _RB_black)
		return ;

	_Node_ptr uncle(getUncle(__x));
	_Node_ptr grand(getGrandParent(__x));

	//부모노드와 같은 레벨의 다른 노드(이하 삼촌노드)도 레드노드라면 규칙 2를 위반, 부모와 삼촌노드를 블랙으로 바꾼 뒤 조부 노드를 빨강으로 칠한 뒤 조부노드부터 룰 위반 재확인
	if (uncle != NULL && uncle->color == _RB_red) {
		__x->parent->color = _RB_black;
		uncle->color = _RB_black;
		grand->color = _RB_red;
		insertion_crack_check(grand);
	}
	else {
		fix_case_second(__x);
	}
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::fix_case_second(_Node_ptr __x)
{
	// 규칙 3. 어떤 노드에서 시작하든 같은 레벨이라면 최하단 리프노드에 도달하기까지 같은 개수의 블랙노드가 있어야 한다. (위의 규칙들을 다 지킨다면 어느정도 균형이 잡히게 된다)

	if (!(is_on_left(__x)) && (is_on_left(__x->parent))) {
		//삽입 후에 __x 노드의 위치를 확인했을 때 삽입된 노드는 오른쪽에 있으며 부모노드도 왼쪽에 있는 경우 rotate_left를 실행 (= 3, 1, 2을 입력했을 경우 2가 1의 부모노드가 되고, 1이 2의 왼쪽 자식 노드가 됨)
		//rotate_left = 오른쪽 자식노드를 부모노드로, 부모노드는 왼쪽 자식노드로 바꾸는것
		rotate_left(__x->parent);
		__x = __x->left;
	}
	else if (is_on_left(__x) && !(is_on_left(__x->parent))) {
		//__x는 왼쪽에 있고 __x의 부모는 오른쪽에 있는 경우 rotate_right를 실행(= 1, 3, 2를 입력했을 경우 2가 3의 부모노드가 되고, 3은 2의 오른쪽 자식 노드가 됨)
		//rotate_right = 왼쪽 자식노드를 부모노드로, 부모노드는 왼쪽 자식노드로 바꾸는것
		rotate_right(__x->parent);
		__x = __x->right;
	}
	fix_case_third(__x);
}

template <typename _Key, typename _Value, typename _Tp, typename _Sel_Key, typename _Sel_Val, typename _Compare, typename _Allocator>
void RBTree<_Key, _Value, _Tp, _Sel_Key, _Sel_Val, _Compare, _Allocator>::fix_case_third(_Node_ptr __x)
{
	_Node_ptr grand(getGrandParent(__x));
	if (grand == __x)
		return ;

	__x->parent->color = _RB_black;
	grand->color = _RB_red;
	if (is_on_left(__x))
		rotate_right(grand);
	else
		rotate_left(grand);
}