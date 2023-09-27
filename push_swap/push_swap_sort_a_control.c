/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_a_control.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:05:54 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 22:15:36 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	a_to_b(t_node **a_top, t_node **b_top, int total, int worst_or_not)
{
	int		num;
	double	chunk;

	chunk = ((0.000000053 * (total * total)) + (0.03 * total) + 14.5);
	num = 0;
	while (*a_top != NULL)
	{
		if (top(a_top) <= num)
		{
			pb(a_top, b_top);
			(num)++;
		}
		else if (num < top(a_top) && top(a_top) <= num + chunk)
		{
			pb(a_top, b_top);
			rb(b_top, PRT);
			(num)++;
		}
		else if (num + chunk < top(a_top) && worst_or_not == NORMAL)
			ra(a_top, PRT);
		else if (num + chunk < top(a_top) && worst_or_not == WORST)
			rra(a_top, PRT);
	}
	b_to_a(a_top, b_top, total);
}
