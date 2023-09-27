/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_doing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:09:22 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 19:55:12 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	dodo(t_node **a_top, t_node **b_top, int option)
{
	if (option == RR && *a_top && *b_top)
	{
		push_bottom(a_top, pop(a_top));
		push_bottom(b_top, pop(b_top));
	}
	if (option == RRR && *a_top && *b_top)
	{
		push(a_top, pop_bottom(a_top));
		push(b_top, pop_bottom(b_top));
	}
}

static int	swap(t_node **top)
{
	t_node	*temp;

	if (*top == NULL || (*top)->next == NULL)
		return (FAIL);
	temp = (*top)->next;
	(*top)->next = (*top)->next->next;
	temp->next = *top;
	*top = temp;
	return (SUC);
}

static int	pushit(char *cmd, t_node **a_top, t_node **b_top)
{
	if (*cmd == 'a')
		push(a_top, pop(b_top));
	else if (*cmd == 'b')
		push(b_top, pop(a_top));
	else
		exit_error();
	return (SUC);
}

static int	rotates(char *cmd, t_node **a_top, t_node **b_top)
{
	if (*cmd == 'a')
		push_bottom(a_top, pop(a_top));
	else if (*cmd == 'b')
		push_bottom(b_top, pop(b_top));
	else if (*(cmd++) == 'r')
	{
		if (*cmd == '\0')
			dodo(a_top, b_top, RR);
		else if (*cmd == 'a')
			push(a_top, pop_bottom(a_top));
		else if (*cmd == 'b')
			push(b_top, pop_bottom(b_top));
		else if (*cmd == '\0')
			dodo(a_top, b_top, RRR);
	}
	else
		exit_error();
	return (SUC);
}

void	doit(char *cmd, t_node **a_top, t_node **b_top)
{
	if (*cmd == 'r')
		rotates((++cmd), a_top, b_top);
	else if (*cmd == 'p')
		pushit((++cmd), a_top, b_top);
	else if (*(cmd++) == 's')
	{
		if (*cmd == 'a')
			swap(a_top);
		else if (*cmd == 'b')
			swap(b_top);
		else if (*cmd == 's')
		{
			swap(a_top);
			swap(b_top);
		}
	}
	else
		exit_error();
}
