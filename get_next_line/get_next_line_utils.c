/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:52:37 by jbak              #+#    #+#             */
/*   Updated: 2022/02/18 16:24:37 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (len1--)
	{
		result[i] = s1[i];
		i++;
	}
	while (len2--)
		result[i++] = *s2++;
	result[i] = '\0';
	if (s1)
		free(s1);
	return (result);
}

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
