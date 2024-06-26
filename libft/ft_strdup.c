/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:38:57 by jbak              #+#    #+#             */
/*   Updated: 2022/07/29 01:22:51 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		cnt;

	cnt = 0;
	while (src[cnt])
		cnt++;
	dest = malloc(sizeof(char) * (cnt + 1));
	if (dest == (void *)0)
		return (NULL);
	cnt = -1;
	while (src[++cnt])
		dest[cnt] = src[cnt];
	dest[cnt] = '\0';
	return (dest);
}
