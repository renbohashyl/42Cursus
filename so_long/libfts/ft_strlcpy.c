/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:20:26 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:19:06 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;
	size_t	srcsize;

	srcsize = 0;
	cnt = 0;
	while (src[srcsize])
		srcsize++;
	if (dstsize > 0)
	{
		while (cnt < (srcsize) && cnt < (dstsize - 1))
			dst[cnt++] = *src++;
		dst[cnt] = '\0';
	}
	return (srcsize);
}
