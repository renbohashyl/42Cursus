/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:17:11 by jbak              #+#    #+#             */
/*   Updated: 2022/07/27 17:44:32 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
