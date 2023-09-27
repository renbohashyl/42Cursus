/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:05:08 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 20:10:43 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	make_free(char **s)
{
	free(*s);
	*s = NULL;
}

static char	*return_nul(char **s, int flag)
{
	char	*nul;

	nul = malloc(1);
	*nul = '\0';
	if (flag)
		make_free(s);
	return (nul);
}

char	*ft_substr(char **s, unsigned int start, size_t len, int flag)
{
	char	*sub;
	char	*temp;

	sub = NULL;
	if (*s == NULL)
		return (NULL);
	else if ((unsigned int)(ft_strlen(*s)) < start || len == 0)
		return (return_nul(s, flag));
	else
	{
		if ((ft_strlen(*s) < len))
			len = ft_strlen(*s);
		temp = malloc(len + 1);
		if (temp)
			ft_strlcpy(temp, (*s + start), (len + 1));
		sub = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	if (sub && flag && *s)
		make_free(s);
	return (sub);
}
