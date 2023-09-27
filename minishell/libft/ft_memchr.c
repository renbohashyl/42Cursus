/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:43:00 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:14:53 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_temp;

	s_temp = (const unsigned char *)s;
	while (n-- > 0)
	{
		if (*s_temp == (unsigned char)c)
			return ((void *)s_temp);
		s_temp++;
	}
	return ((void *)0);
}
