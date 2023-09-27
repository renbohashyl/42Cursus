/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:23:12 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:23:13 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && size > 0)
	{
		dest[i] = src[i];
		++i;
		--size;
	}
	dest[i] = '\0';
	return (dest);
}
