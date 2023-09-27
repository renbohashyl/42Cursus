/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:11:32 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 22:15:36 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	r_or_rr(t_node **vtop, int cnt, int option, char stack)
{
	if (stack == 'a')
	{
		if (option == RR)
			while (cnt-- > 0)
				rra(vtop, PRT);
		else if (option == R)
			while (cnt-- > 0)
				ra(vtop, PRT);
	}
	if (stack == 'b')
	{
		if (option == RR)
			while (cnt-- > 0)
				rrb(vtop, PRT);
		else if (option == R)
			while (cnt-- > 0)
				rb(vtop, PRT);
	}
}

int	search(t_node *vtop, int nbr)
{
	int	cnt;

	cnt = 0;
	while (vtop && top(&vtop) != nbr)
	{
		vtop = (vtop)->next;
		cnt++;
	}
	if (!vtop || top(&vtop) != nbr)
		return (ERROR);
	return (cnt);
}

static int	check_desc(t_node *vtop, int total)
{
	int	cnt;
	int	size;
	int	flag;

	flag = 0;
	cnt = 0;
	while (vtop)
	{
		size = 5 + (total / 50);
		flag = 0;
		while (size-- > 0 && vtop)
		{
			if (top(&vtop) < top(&((vtop)->next)))
				flag = 1;
			vtop = (vtop)->next;
		}
		if (flag == 0)
			cnt++;
	}
	return (cnt);
}

int	main(int cnt, char **array)
{
	t_stack	a;
	t_stack	b;
	int		total;

	if (cnt < 2)
		return (0);
	a.top = NULL;
	b.top = NULL;
	total = parse_digits(cnt, array, &a.top);
	if (((double)check_desc(a.top, total) / (double)(5 + (total / 50)) >= 0.85))
		sort(&a.top, &b.top, total, WORST);
	else
		sort(&a.top, &b.top, total, NORMAL);
	return (0);
}
