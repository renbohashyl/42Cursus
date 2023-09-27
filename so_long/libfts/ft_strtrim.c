/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:43:04 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:19:32 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	long	idx;
	long	jdx;
	long	stidx;
	char	*stemp;

	idx = 0;
	stidx = 0;
	jdx = (ft_strlen(s1) - 1);
	if (*s1 != '\0')
	{
		while (s1[idx] && ft_strchr(set, s1[idx]))
			idx++;
		while (s1[jdx] && ft_strchr(set, s1[jdx]) && jdx > idx)
			jdx--;
		stemp = malloc((jdx - idx) + 2);
		if (stemp)
		{
			while (idx <= jdx)
				stemp[stidx++] = s1[idx++];
			stemp[stidx] = '\0';
		}
	}
	else
		stemp = ft_calloc(1, 1);
	return (stemp);
}
