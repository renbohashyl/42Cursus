/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:17:32 by jbak              #+#    #+#             */
/*   Updated: 2021/12/01 20:17:32 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*iteration_strnstr(const char *s, const char *find, size_t slen)
{
	const char	*ffind;

	ffind = find;
	while (slen-- > 0)
	{
		if (*ffind == '\0')
			return ((char *)(s - (ffind - find)));
		else if (*s == *ffind)
			ffind++;
		else
		{
			if (ffind > find)
			{
				s -= (ffind - find) - 1;
				slen++;
			}
			ffind = find;
			if (*s == *ffind)
				ffind++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	return ((void *)0);
}

char	*ft_strnstr(const char *s, const char *find, size_t slen)
{
	if (!(*find))
		return ((char *)s);
	if (ft_strlen(find) == slen || ft_strlen(s) == slen)
		slen++;
	return (iteration_strnstr(s, find, slen));
}
