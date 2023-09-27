/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:19:59 by jbak              #+#    #+#             */
/*   Updated: 2022/07/27 17:28:10 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	long	cnt;

	cnt = 0;
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str != (void *)0)
	{
		while (s1 && *s1)
			str[cnt++] = (char)*s1++;
		while (s2 && *s2)
			str[cnt++] = (char)*s2++;
		str[cnt] = '\0';
	}
	return (str);
}
