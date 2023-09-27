/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_numbers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:15:50 by jbak              #+#    #+#             */
/*   Updated: 2022/03/24 15:54:14 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	prt_deci(int nbr)
{
	long	nb;
	int		i;
	int		ret;
	char	num[INT_DIGIT + 1];

	nb = nbr;
	ret = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	if (nb < 0)
	{
		ret += write(1, "-", 1);
		nb = -nb;
	}
	i = 0;
	while (nb > 0)
	{
		num[i] = nb % 10 + 0x30;
		nb /= 10;
		i++;
	}
	num[i] = '\0';
	while (--i >= 0)
		ret += write(1, &num[i], 1);
	return (ret);
}

int	prt_u_deci(unsigned int nbr)
{
	int		i;
	int		ret;
	char	num[INT_DIGIT + 1];

	ret = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	i = 0;
	while (nbr > 0)
	{
		num[i] = nbr % 10 + 0x30;
		nbr /= 10;
		i++;
	}
	num[i] = '\0';
	while (--i >= 0)
		ret += write(1, &num[i], 1);
	return (ret);
}

int	prt_hexa(unsigned int nbr, int low_up)
{
	int		i;
	int		ret;
	char	num[INT_DIGIT + 1];

	i = 0;
	ret = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	while (nbr > 0)
	{
		num[i] = DIGIT[nbr % 16] | (SMALL * low_up);
		nbr /= 16;
		i++;
	}
	num[i] = '\0';
	while (--i >= 0)
		ret += write(1, &num[i], 1);
	return (ret);
}

int	prt_addr(unsigned long long nbr)
{
	char	num[(ADDR_MAX * (sizeof(long) / 4) + 1)];
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (nbr == 0)
		return (write(1, "0x0", 3));
	ret += write(1, "0x", 2);
	while (nbr > 0)
	{
		num[i] = (DIGIT[nbr % 16] | SMALL);
		nbr /= 16;
		i++;
	}
	num[i] = '\0';
	while (--i >= 0)
		ret += write(1, &num[i], 1);
	return (ret);
}
