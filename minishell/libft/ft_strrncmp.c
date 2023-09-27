/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 00:10:17 by jbak              #+#    #+#             */
/*   Updated: 2022/10/12 18:02:02 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 && s2)
		return (*s2);
	else if (s1 && !s2)
		return (*s1);
	while (s1 && *s1)
		s1++;
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1--;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
