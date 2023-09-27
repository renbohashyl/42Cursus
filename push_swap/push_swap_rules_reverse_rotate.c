/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rules_reverse_rotate.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:45:43 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:38:59 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rra(t_node	**a_top, int option)
{
	push(a_top, pop_bottom(a_top));
	if (option == PRT)
		write(STDOUT, "rra\n", 4);
	return (SUC);
}

int	rrb(t_node	**b_top, int option)
{
	push(b_top, pop_bottom(b_top));
	if (option == PRT)
		write(STDOUT, "rrb\n", 4);
	return (SUC);
}

int	rrr(t_node **a_top, t_node **b_top)
{
	rra(a_top, NON);
	rrb(b_top, NON);
	write(STDOUT, "rrr\n", 4);
	return (SUC);
}
