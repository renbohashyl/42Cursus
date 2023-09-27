/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:39:55 by jbak              #+#    #+#             */
/*   Updated: 2022/08/06 02:06:33 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	idx;

	idx = 0;
	while (s && s[idx] != (char)c)
	{
		if (s[idx] == '\0')
			return ((void *)0);
		idx++;
	}
	return ((char *)(s + idx));
}
