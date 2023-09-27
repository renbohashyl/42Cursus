/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_libft.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:14:49 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:32:39 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	exit_error(void)
{
	write (2, "Error\n", 6);
	exit(0);
}

int	ft_issp(int c)
{
	return ((c >= 0x09 && c <= 0x0D) || (c == 0x20));
}

int	ft_isnum(int c)
{
	return ((c >= 0x30 && c <= 0x39));
}

int	ft_atoi(const char *nptr)
{
	long long	num;
	int			sign;

	sign = 1;
	num = 0;
	while (ft_issp(*nptr))
		nptr++;
	if (sign == 1 && num == 0 && *nptr == '\0')
		exit_error();
	if ((*nptr == '-' || *nptr == '+') && nptr[1] != '\0')
		if (*(nptr++) == '-')
			sign = -1;
	while (ft_isnum(*nptr))
	{
		num = (num * 10) + (*(nptr++) - 0x30);
		if (num < INT_MIN || num > INT_MAX)
		{
			if (sign < 0 && num == 2147483648)
				continue ;
			exit_error();
		}
	}
	if (*nptr != '\0')
		exit_error();
	return (num * sign);
}
