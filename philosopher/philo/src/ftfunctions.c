/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftfunctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:22:13 by jbak              #+#    #+#             */
/*   Updated: 2022/08/28 19:11:57 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

size_t	ft_strlen(char *str)
{
	int	idx;

	idx = -1;
	while (str[idx])
		idx++;
	return (idx);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while ((*nptr >= 0x09 && *nptr <= 0x0D) || *nptr == 0x20)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= 0x30 && *nptr <= 0x39)
	{
		if (sign > 0 && ((long)num * 10) > (INT_MAX - (*nptr - 0x30)))
			return (-1);
		if (sign < 0 && ((long)num * 10) < (INT_MIN - ((*nptr - 0x30) * -1)))
			return (0);
		num = (num * 10) + (*nptr++ - 0x30);
	}
	return (num * sign);
}

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	if (len)
		while (len-- > 0)
			*temp++ = 0;
}

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
