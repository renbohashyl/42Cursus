/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stack_control.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:10:12 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 16:54:09 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_node **top, t_node *arg)
{
	if (*top && arg)
	{
		(arg)->next = *top;
		*top = arg;
	}
	else if (arg && !(*top))
		*top = arg;
	else
		return ;
}

t_node	*pop(t_node **top)
{
	t_node	*temp;

	if (*top)
	{
		temp = *top;
		(*top) = (*top)->next;
		(temp)->next = NULL;
		return (temp);
	}
	else
		return (NULL);
}

void	push_bottom(t_node **top, t_node *arg)
{
	t_node	*start;

	if (*top && arg)
	{
		start = *top;
		while ((*top)->next != NULL)
			*top = (*top)->next;
		(*top)->next = arg;
		arg->next = NULL;
		*top = start;
	}
	else if (arg && !(*top))
		*top = arg;
	else
		return ;
}

t_node	*pop_bottom(t_node **top)
{
	t_node	*start;
	t_node	*temp;
	t_node	*pre;

	start = *top;
	if (*top && (*top)->next != NULL)
	{
		while ((*top)->next != NULL)
		{
			pre = (*top);
			*top = (*top)->next;
		}
		temp = (*top);
		(pre)->next = NULL;
		*top = start;
		return (temp);
	}
	else if (*top && (*top)->next == NULL)
		return (pop(top));
	else
		return (NULL);
}

int	top(t_node **vtop)
{
	if (*vtop == NULL)
		return (-2147483648);
	else
		return ((*vtop)->index);
}
