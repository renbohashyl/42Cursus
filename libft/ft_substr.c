/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:05:08 by jbak              #+#    #+#             */
/*   Updated: 2022/07/28 20:26:05 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (s == (void *)0)
		return ((void *)0);
	else if ((unsigned int)(ft_strlen(s)) < start || len == 0)
	{
		sub = malloc(1);
		*sub = '\0';
		return (sub);
	}
	else
	{
		if ((ft_strlen(s) < len))
			len = ft_strlen(s);
		sub = malloc(len + 1);
		if (sub)
			ft_strlcpy (sub, (s + start), (len + 1));
	}
	return (sub);
}
