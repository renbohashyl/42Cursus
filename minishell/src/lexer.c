/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:37 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:37 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	select_val_case(char *str, int len)
{
	if (len == 1)
	{
		if (*str == '<')
			return (TYPE_REDIREC_SIG_IN);
		else if (*str == '>')
			return (TYPE_REDIREC_SIG_OUT);
		else if (*str == '|')
			return (TYPE_PIPE);
	}
	if (len == 2)
	{
		if (*str == '>')
		{
			if (*(++str) == '>')
				return (TYPE_REDIREC_DOB_OUT);
			return (TYPE_WORD);
		}
		else if (*str == '<')
		{
			if (*(++str) == '<')
				return (TYPE_REDIREC_DOB_IN);
			return (TYPE_WORD);
		}
	}
	return (TYPE_WORD);
}

int	search_pipe(t_word *word)
{
	int	cnt;

	cnt = 0;
	while (word)
	{
		if (word->type == TYPE_PIPE)
			cnt++;
		word = word->next_word;
	}
	return (cnt);
}

void	remove_qutoes(char *s1, char *s2, int toggle)
{
	while (*s2)
	{
		if (*s2 == '\"')
		{
			toggle = !toggle;
			s2++;
		}
		else if (*s2 == '\'' && toggle)
			*s1++ = *s2++;
		else if (*s2 == '\'' && !toggle)
		{
			s2++;
			while (*s2 && *s2 != '\'')
				*s1++ = *s2++;
			if (*s2 == '\'')
				s2++;
		}
		else if (*s2 != '\0')
			*s1++ = *s2++;
	}
	*s1 = '\0';
}

void	lexing_type(t_word *word)
{
	word = word->next_word;
	while (word)
	{
		if (word->type == TYPE_WORD)
		{
			if (word->prev_word->type == TYPE_PIPE)
				word->type = TYPE_CMD;
			else if (word->prev_word->type == TYPE_REDIREC_SIG_OUT || \
				word->prev_word->type == TYPE_REDIREC_DOB_OUT || \
				word->prev_word->type == TYPE_REDIREC_SIG_IN || \
				word->prev_word->type == TYPE_REDIREC_DOB_IN)
				word->type = TYPE_FILENAME;
		}
		word = word->next_word;
	}
}

t_word	*lexer_word(t_node *node, t_env *envs)
{
	t_word	*word;
	t_word	*word_tmp;
	t_node	*child;

	child = node;
	word = 0;
	while (child)
	{
		word_tmp = word_expand(child->value, envs);
		if (!word_tmp)
			return (NULL);
		child = child->next_sibling;
		if (!word)
			word = word_tmp;
		else
			if (add_each_word(word, word_tmp, envs))
				return (free_word_tree(word));
	}
	word_tmp = word;
	word->total_pipe = search_pipe(word_tmp);
	lexing_type(word_tmp);
	return (word);
}
