/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:01:42 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:17:58 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*dest_temp;
	const unsigned char	*src_temp;
	unsigned char		*last_of_dest;
	const unsigned char	*last_of_src;

	if (dest == src || len == 0)
		return (dest);
	dest_temp = (unsigned char *)dest;
	src_temp = (const unsigned char *)src;
	last_of_dest = dest_temp + len - 1;
	last_of_src = src_temp + len - 1;
	if (dest_temp < src_temp)
		while (len-- > 0)
			*dest_temp++ = *src_temp++;
	if (dest_temp > src_temp)
		while (len-- > 0)
			*last_of_dest-- = *last_of_src--;
	return (dest);
}
