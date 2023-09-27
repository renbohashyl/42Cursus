/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_characters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:15:46 by jbak              #+#    #+#             */
/*   Updated: 2022/03/24 15:48:08 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	prt_char(va_list va)
{
	char	c;

	c = va_arg(va, int);
	return (write(1, &c, 1));
}

int	prt_str(va_list va)
{
	char	*str;
	int		i;

	str = va_arg(va, char *);
	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}
