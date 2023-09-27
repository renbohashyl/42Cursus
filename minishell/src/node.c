/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:40 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:40 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "node.h"

//creates a new node set type field.
t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

void	add_child_node(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent || !child)
		return ;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
		{
			sibling = sibling->next_sibling;
		}
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

void	set_node_val_str(t_node *node, char *val)
{
	char	*tmp;

	if (!val)
		node->value = NULL;
	else
	{
		tmp = malloc(ft_strlen(val) + 1);
		if (!tmp)
			node->value = NULL;
		else
		{
			ft_strcpy(tmp, val);
			node->value = tmp;
		}
	}
}

t_node	*free_node_tree(t_node *node)
{
	t_node	*child;
	t_node	*next;

	if (!node)
		return (0);
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	if (node->value)
		free(node->value);
	free(node);
	return (0);
}
