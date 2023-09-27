/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:00:37 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:14:57 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*st1;
	const unsigned char	*st2;

	st1 = (const unsigned char *)s1;
	st2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*st1 != *st2)
			break ;
		n--;
		st1++;
		st2++;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)st1 - *(unsigned char *)st2);
}
