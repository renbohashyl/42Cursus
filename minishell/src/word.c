/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:54 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:57 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	*free_word_tree(t_word *word)
{
	t_word	*next;

	if (!word)
		return (NULL);
	while (word)
	{
		next = word->next_word;
		if (word->data)
			free(word->data);
		free(word);
		word = next;
	}
	free(word);
	word = NULL;
	return (NULL);
}

t_word	*make_word(char *str)
{
	t_word	*word;
	char	*data;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->word_len = ft_strlen(str);
	word->type = select_val_case(str, word->word_len);
	data = malloc(word->word_len + 1);
	if (!data)
	{
		free(word);
		return (NULL);
	}
	ft_strcpy(data, str);
	word->data = data;
	word->next_word = NULL;
	word->prev_word = NULL;
	word->total_pipe = 0;
	free(str);
	return (word);
}

int	add_each_word(t_word *prev, t_word *next, t_env *envs)
{
	t_word	*tmp;

	if (!prev || !next)
		return (0);
	tmp = prev;
	while (tmp->next_word)
		tmp = tmp->next_word;
	tmp->next_word = next;
	next->prev_word = tmp;
	if ((ft_strncmp(tmp->data, "<<", -1) == 0) && next)
		return (expand_redirection(next->data, envs));
	return (0);
}
