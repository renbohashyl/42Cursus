/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:01:51 by jbak              #+#    #+#             */
/*   Updated: 2021/12/06 01:44:11 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	idx;
	size_t			len;

	idx = 0;
	len = ft_strlen(s);
	if (!s || !f || !(len))
		return ;
	while (idx < len)
	{
		f(idx, s + idx);
		idx++;
	}
	s[idx] = '\0';
}
