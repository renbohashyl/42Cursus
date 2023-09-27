/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:01:51 by jbak              #+#    #+#             */
/*   Updated: 2021/12/06 01:44:27 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	char			*str;
	size_t			len;

	if (!s || !f)
		return ((void *)0);
	idx = 0;
	len = ft_strlen(s);
	str = malloc(len + 1);
	if (str == (void *)0)
		return ((void *)0);
	while (idx < len)
	{
		str[idx] = f(idx, s[idx]);
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
