/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:13:27 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:46:23 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	two(t_node **vtop)
{
	t_node	*scd;

	scd = (*vtop)->next;
	if ((scd)->value < (*vtop)->value)
		sa(vtop, PRT);
}

static void	three(t_node **vtop)
{
	t_node	*scd;
	t_node	*trd;

	scd = (*vtop)->next;
	trd = (*vtop)->next->next;
	if ((scd)->value < (*vtop)->value && (*vtop)->value < (trd)->value)
		sa(vtop, PRT);
	else if ((scd)->value < (trd)->value && (trd)->value < (*vtop)->value)
		ra(vtop, PRT);
	else if ((trd)->value < (*vtop)->value && (*vtop)->value < (scd)->value)
		rra(vtop, PRT);
	else if ((*vtop)->value < (trd)->value && (trd)->value < (scd)->value)
	{
		rra(vtop, PRT);
		sa(vtop, PRT);
	}
	else if ((trd)->value < (scd)->value && (scd)->value < (*vtop)->value)
	{
		sa(vtop, PRT);
		rra(vtop, PRT);
	}
}

static void	five(t_node **a_top, t_node **b_top)
{
	int		where;
	int		cnt;
	int		num;

	cnt = 4;
	num = 2;
	while (cnt >= 0)
	{
		where = search(*a_top, cnt);
		if (where > num)
			r_or_rr(a_top, (4 - where), RR, 'a');
		else if (where <= num)
			r_or_rr(a_top, (where), R, 'a');
		pb(a_top, b_top);
		cnt -= 4;
	}
	three(a_top);
	pa(a_top, b_top);
	pa(a_top, b_top);
	ra(a_top, PRT);
}

static int	check_a(t_node *vtop)
{
	while (vtop != NULL && (vtop)->next != NULL)
	{
		if (((vtop)->value) > (((vtop)->next)->value))
			return (FAIL);
		vtop = (vtop)->next;
	}
	if (vtop == NULL || (vtop)->next == NULL)
		return (SUC);
	return (ERROR);
}

void	sort(t_node **a_top, t_node **b_top, int total, int worst_or_not)
{
	if (check_a(*a_top))
		return ;
	if (total == 2)
		two(a_top);
	else if (total == 3)
		three(a_top);
	else if (total == 5)
		five(a_top, b_top);
	else
		a_to_b(a_top, b_top, total, worst_or_not);
}
