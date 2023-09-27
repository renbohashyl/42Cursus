/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:12:56 by jbak              #+#    #+#             */
/*   Updated: 2022/08/06 05:23:23 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ldest;
	size_t	lsrc;
	size_t	idx;

	ldest = ft_strlen(dest);
	lsrc = ft_strlen(src);
	if (ldest >= size)
		return (lsrc + size);
	if (size == 0)
		return (lsrc);
	idx = 0;
	if (ldest < size - 1)
	{
		while (src[idx] != '\0' && idx < (size - 1 - ldest))
		{
			dest[ldest + idx] = src[idx];
			idx++;
		}
	}
	dest[ldest + idx] = '\0';
	return (ldest + lsrc);
}
