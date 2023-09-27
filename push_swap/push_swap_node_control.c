/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_node_control.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:29:17 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:37:18 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ft_nn(int value)
{
	t_node	*newnode;

	newnode = malloc(sizeof(t_node));
	if (newnode)
	{
		newnode->value = value;
		newnode->index = 0;
		newnode->next = NULL;
	}
	else
		write(STDOUT, "\tMalloc Error\n", 14);
	return (newnode);
}
