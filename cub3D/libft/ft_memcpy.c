/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:15:06 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:15:02 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*temp;

	if (dest == src)
		return (dest);
	temp = (unsigned char *)dest;
	while (len-- > 0)
		*temp++ = *(unsigned char *)src++;
	return (dest);
}
