/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_rules_swap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:31:58 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:38:58 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(t_node **top, int option)
{
	t_node	*temp;

	if (*top == NULL || (*top)->next == NULL)
		return (FAIL);
	temp = (*top)->next;
	(*top)->next = (*top)->next->next;
	temp->next = *top;
	*top = temp;
	if (option == PRT)
		write(STDOUT, "sa\n", 3);
	return (SUC);
}

int	sb(t_node **top, int option)
{
	t_node	*temp;

	if (*top == NULL || (*top)->next == NULL)
		return (FAIL);
	temp = (*top)->next;
	(*top)->next = (*top)->next->next;
	temp->next = *top;
	*top = temp;
	if (option == PRT)
		write(STDOUT, "sb\n", 3);
	return (SUC);
}

int	ss(t_node **a_top, t_node **b_top)
{
	sa(a_top, NON);
	sb(b_top, NON);
	write(STDOUT, "ss\n", 3);
	return (SUC);
}
