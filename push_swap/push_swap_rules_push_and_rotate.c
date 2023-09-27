/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rules_push_and_rotate.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:44:07 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:41:34 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pa(t_node **a_top, t_node **b_top)
{
	if (*b_top == NULL)
		return (FAIL);
	if (*b_top)
	{
		push(a_top, pop(b_top));
		write(STDOUT, "pa\n", 3);
	}
	return (SUC);
}

int	pb(t_node **a_top, t_node **b_top)
{
	if (*a_top == NULL)
		return (FAIL);
	if (*a_top)
	{
		push(b_top, pop(a_top));
		write(STDOUT, "pb\n", 3);
	}
	return (SUC);
}

int	ra(t_node **a_top, int option)
{
	push_bottom(a_top, pop(a_top));
	if (option == PRT)
		write(STDOUT, "ra\n", 3);
	return (SUC);
}

int	rb(t_node **b_top, int option)
{
	push_bottom(b_top, pop(b_top));
	if (option == PRT)
		write(STDOUT, "rb\n", 3);
	return (SUC);
}

int	rr(t_node **a_top, t_node **b_top)
{
	ra(a_top, NON);
	rb(b_top, NON);
	write(STDOUT, "rr\n", 3);
	return (SUC);
}
