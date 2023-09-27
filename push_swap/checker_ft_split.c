/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ft_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:09:30 by jbak              #+#    #+#             */
/*   Updated: 2022/06/05 20:01:22 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	word_count(char const *s)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	while (s[idx])
	{
		if (ft_issp(s[idx]))
			idx++;
		else
		{
			cnt++;
			while (s[idx] && !ft_issp(s[idx]))
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

void	*make_free(char **split)
{
	size_t	idx;

	idx = 0;
	while (split[idx] != NULL)
		free(split[idx++]);
	free(split);
	return (NULL);
}

static char	**make_split(char **split, char const *s, int w)
{
	int	sdx;
	int	idx;
	int	len_of_word;

	sdx = 0;
	idx = 0;
	len_of_word = 0;
	while (s[sdx] && idx < w)
	{
		while (ft_issp(s[sdx]) && s[sdx])
			sdx++;
		while (!ft_issp(s[sdx]) && s[sdx])
		{
			sdx++;
			len_of_word++;
		}
		split[idx] = malloc(len_of_word + 1);
		if (split[idx] == ((void *)0))
			return (make_free(split));
		putin(split[idx], s, sdx, len_of_word);
		len_of_word = 0;
		idx++;
	}
	split[idx] = NULL;
	return (split);
}

char	**ft_split(char const *s)
{
	int		cnt_words;
	char	**split;

	if (!(*s))
	{
		split = malloc(sizeof(char *));
		split[0] = (void *)0;
		return (split);
	}
	cnt_words = word_count(s);
	split = malloc(sizeof(char *) * (cnt_words + 1));
	if (split != NULL)
		make_split(split, s, cnt_words);
	return (split);
}
