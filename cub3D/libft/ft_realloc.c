/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:22:26 by jbak              #+#    #+#             */
/*   Updated: 2022/11/15 19:22:29 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *buf, size_t len)
{
	void	*new_buf;

	if (len == 0 && buf)
	{
		free(buf);
		return (NULL);
	}
	if (!buf)
		return (malloc(sizeof(len)));
	new_buf = malloc(len);
	if (!new_buf)
		return (buf);
	new_buf = ft_memcpy(new_buf, buf, len);
	free(buf);
	return (new_buf);
}
