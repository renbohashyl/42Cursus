/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:19:59 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 18:34:01 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char **s1, char const *s2, int flag)
{
	char	*str;
	long	cnt;
	int		idx;

	cnt = 0;
	idx = 0;
	str = malloc(sizeof(char) * ((ft_strlen(*s1) + ft_strlen(s2)) + 1));
	if (str != (void *)0)
	{
		while (*s1 && (*s1)[idx])
			str[cnt++] = (*s1)[idx++];
		idx = 0;
		while (s2 && s2[idx])
			str[cnt++] = s2[idx++];
		str[cnt] = '\0';
	}
	if (flag && *s1)
		free(*s1);
	*s1 = NULL;
	return (str);
}
