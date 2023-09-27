/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_libft.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:11:32 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 21:29:19 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
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
				return (num * sign);
			exit_error();
		}
	}
	if (*nptr != '\0')
		exit_error();
	return (num * sign);
}
