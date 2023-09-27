/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:04 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:05 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "libft.h"
# include "defs_for_minishell.h"
# include "minishell.h"

t_node	*new_node(t_node_type type);
t_node	*free_node_tree(t_node *node);
void	add_child_node(t_node *parent, t_node *child);
void	set_node_val_str(t_node *node, char *val);

#endif
