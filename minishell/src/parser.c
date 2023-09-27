/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:43 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:44 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*connect_command(t_token *tok, t_src *src, t_node *cmd)
{
	t_node	*word;

	while (tok)
	{
		if (tok->text[0] == '\n')
		{
			free_token(tok);
			break ;
		}
		word = new_node(NODE_VAR);
		if (!word)
		{
			free_token(tok);
			return (NULL);
		}
		set_node_val_str(word, tok->text);
		add_child_node(cmd, word);
		free_token(tok);
		tok = tokenize(src);
		if (word && (!tok && (src->cur_pos != src->bufsize)))
			return (free_node_tree(cmd));
	}
	return (cmd);
}

t_node	*parse_simple_command(t_token *tok)
{
	t_node	*cmd;
	t_src	*src;

	if (!tok)
		return (NULL);
	cmd = new_node(NODE_COMMAND);
	if (!cmd)
	{
		free_token(tok);
		return (NULL);
	}
	src = tok->src;
	cmd = connect_command(tok, src, cmd);
	return (cmd);
}

int	parse_and_execute(t_src *src, t_env *envs)
{
	t_token	*tok;
	t_node	*cmd;

	skip_white_spaces(src);
	tok = tokenize(src);
	if (!tok)
		return (0);
	cmd = parse_simple_command(tok);
	if (!cmd)
		return (0);
	if (!src && tok)
		free_token(tok);
	return (executor(cmd, envs));
}
