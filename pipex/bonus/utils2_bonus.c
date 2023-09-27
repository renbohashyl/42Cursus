/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:52:37 by jbak              #+#    #+#             */
/*   Updated: 2022/09/09 19:28:19 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	while (*s)
	{
		if (*s == cc)
			return ((char *)s);
		s++;
	}
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		isit;
	int		len;
	int		i;

	isit = 0;
	len = 0;
	i = 0;
	if (ft_strchr(s, '\n'))
		isit = 1;
	while (s[len] && s[len] != '\n')
		len++;
	str = (char *)malloc(len + 1 + isit);
	if (!str)
		return (NULL);
	while (len--)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\n';
	str[i + isit] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	sub = (char *)malloc(len + 1);
	if (!sub)
	{
		free(s);
		s = NULL;
		return (NULL);
	}
	while (len-- && s[start] != '\0')
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	free(s);
	s = NULL;
	return (sub);
}

int	shift_after_slash(char *cmd)
{
	size_t	idx;
	size_t	slash;

	idx = -1;
	slash = 0;
	while (cmd && cmd[++idx])
		if (cmd[idx] == '/')
			slash = idx + 1;
	return (slash);
}
