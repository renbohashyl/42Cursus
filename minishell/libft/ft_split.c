/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:40:21 by jbak              #+#    #+#             */
/*   Updated: 2022/10/06 16:21:42 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char const del)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	if (!s)
		return (0);
	while (s[idx])
	{
		if (s[idx] == del)
			idx++;
		else
		{
			cnt++;
			while (s[idx] && s[idx] != del)
				idx++;
		}
	}
	return (cnt);
}

static char	*putin(char	*splited, char const *s, int sdx, int len_of_word)
{
	int	i;

	i = 0;
	while (len_of_word > 0)
		splited[i++] = s[sdx - len_of_word--];
	splited[i] = '\0';
	return (splited);
}

void	*make_free(char ***split)
{
	unsigned int	idx;

	idx = 0;
	while ((*split)[idx])
		free((*split)[idx++]);
	free(*split);
	return (0);
}

static char	**make_split(char **split, char const *s, char const del, int w)
{
	int	sdx;
	int	idx;
	int	len_of_word;

	sdx = 0;
	idx = 0;
	len_of_word = 0;
	while (s[sdx] && idx < w)
	{
		while (s[sdx] && s[sdx] == del)
			sdx++;
		while (s[sdx] && s[sdx] != del)
		{
			sdx++;
			len_of_word++;
		}
		split[idx] = malloc(len_of_word + 1);
		if (split[idx] == ((void *)0))
			return (make_free(&split));
		putin(split[idx], s, sdx, len_of_word);
		len_of_word = 0;
		idx++;
	}
	split[idx] = ((void *)0);
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		cnt_words;
	char	**split;

	if (!(*s))
	{
		split = malloc(sizeof(char *));
		split[0] = (void *)0;
		return (split);
	}
	cnt_words = word_count(s, c);
	split = malloc(sizeof(char *) * (cnt_words + 1));
	if (split != (void *)0)
		make_split(split, s, c, cnt_words);
	return (split);
}
