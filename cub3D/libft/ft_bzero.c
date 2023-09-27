/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:49:00 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:14:17 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	if (len)
		while (len-- > 0)
			*temp++ = 0;
}
