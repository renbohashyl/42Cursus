/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:58:32 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:33:15 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*idx(t_node **vtop, t_node *newnode)
{
	t_node	*start;

	start = *vtop;
	while (*vtop)
	{
		if ((*vtop)->value > (newnode)->value)
			((*vtop)->index) += 1;
		else if ((*vtop)->value < (newnode)->value)
			((newnode)->index) += 1;
		(*vtop) = (*vtop)->next;
	}
	*vtop = start;
	return (newnode);
}

static ssize_t	errchk(char **array)
{
	int	idx;
	int	jdx;
	int	total;

	idx = 0;
	total = 0;
	while (array[++idx] != NULL)
	{
		jdx = -1;
		while (array[idx][++jdx] != '\0')
		{
			if ((ft_isnum(array[idx][jdx])) && \
				((ft_issp(array[idx][jdx + 1]) || array[idx][jdx + 1] == '\0')))
				total++;
			else if (ft_isnum(array[idx][jdx]) || ft_issp(array[idx][jdx]) || \
					array[idx][jdx] == '-')
				continue ;
			else
				exit_error();
		}
		if (array[idx][0] == '\0' || total == 0)
			exit_error();
	}
	return (total);
}

static void	dup_inspect(t_node **start)
{
	t_node	*temp;
	t_node	*top;

	if (!(*start))
		return ;
	top = *start;
	while (top != NULL)
	{
		temp = top->next;
		while (temp != NULL && temp->value != top->value)
			temp = temp->next;
		if (temp != NULL)
			break ;
		top = top->next;
	}
	if (temp != NULL && temp->value == top->value)
	{
		while (*start != NULL)
			free(pop(start));
		exit_error();
	}
}

int	parse_digits(int cnt, char **array, t_node **top)
{
	char	**splt;
	int		cdx;
	int		sdx;
	int		tal;

	cdx = 0;
	tal = errchk(array);
	while (++cdx < cnt)
	{
		sdx = 0;
		if (ft_strlen(array[cdx]) >= 2)
		{
			splt = ft_split(array[cdx]);
			while (splt[sdx] != NULL)
				push_bottom(top, idx(top, ft_nn(ft_atoi(splt[sdx++]))));
			make_free(splt);
		}
		else if (ft_strlen(array[cdx]) < 2)
			push_bottom(top, idx(top, ft_nn(ft_atoi(array[cdx]))));
	}
	if (tal != ERROR)
		dup_inspect(top);
	return (tal);
}
