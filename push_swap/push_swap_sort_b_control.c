/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_b_control.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:29:37 by jbak              #+#    #+#             */
/*   Updated: 2022/06/03 17:19:57 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	b_search(t_node *b_top, int maxvalue)
{
	int		count;

	count = 0;
	while (b_top && (b_top)->next)
	{
		if (top(&b_top) == (maxvalue - 1))
			break ;
		b_top = (b_top)->next;
		count++;
	}
	if ((b_top)->next == NULL && top(&b_top) != (maxvalue - 1))
		return (ERROR);
	else if (b_top == NULL)
		return (ERROR);
	return (count);
}

static void	doit(t_node **a_top, t_node **b_top, int maxv)
{
	int	cnt;

	cnt = b_search(*b_top, maxv);
	if (cnt > (maxv / 2))
	{
		r_or_rr(b_top, (maxv - cnt), RR, 'b');
		pa(a_top, b_top);
	}
	else if (-1 < cnt && cnt <= (maxv / 2))
	{
		r_or_rr(b_top, cnt, R, 'b');
		pa(a_top, b_top);
	}
	if (cnt == ERROR)
		return ;
}

void	b_to_a(t_node **a_top, t_node **b_top, int total)
{
	int	maxvalue;

	maxvalue = total;
	while (*b_top)
		doit(a_top, b_top, maxvalue--);
}
