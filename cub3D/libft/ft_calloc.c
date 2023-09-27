/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:22:13 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:14:23 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbyte, size_t size)
{
	void	*ptr;

	if (nbyte == 0 || size == 0)
	{
		nbyte = 1;
		size = 1;
	}
	ptr = malloc (nbyte * size);
	if (ptr != (void *)0)
		ft_bzero(ptr, nbyte * size);
	return (ptr);
}
