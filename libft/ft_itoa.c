/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:15:51 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:14:49 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_digits(int n)
{
	int	cnt;

	cnt = 0;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*make_str(long long int ln, int num)
{
	int		neg;
	char	*str;

	neg = 0;
	str = malloc(num + 2);
	if (str == (void *)0)
		return ((void *)0);
	if (ln < 0)
	{
		num += 1;
		str[0] = '-';
		ln *= -1;
		neg = 1;
	}
	str[num] = '\0';
	while (num-- > neg)
	{
		str[num] = ((ln % 10) + 0x30);
		ln /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long long int	ln;
	char			*str;
	int				num;

	ln = n;
	num = num_of_digits(n);
	if (n == 0)
	{
		str = malloc(2);
		str[0] = 0x30;
		str[1] = '\0';
	}
	else
		str = make_str(ln, num);
	return (str);
}
