/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:15:36 by jbak              #+#    #+#             */
/*   Updated: 2022/03/24 15:47:59 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_check(char arg, va_list va)
{
	if (arg == 'c')
		return (prt_char(va));
	if (arg == 's')
		return (prt_str(va));
	if (arg == 'p')
		return (prt_addr(va_arg(va, unsigned long)));
	if (arg == 'd' || arg == 'i')
		return (prt_deci(va_arg(va, int)));
	if (arg == 'u')
		return (prt_u_deci(va_arg(va, unsigned int)));
	if (arg == 'x')
		return (prt_hexa(va_arg(va, unsigned int), LOWER));
	if (arg == 'X')
		return (prt_hexa(va_arg(va, unsigned int), UPPER));
	if (arg == '%')
		return (write(1, "%", 1));
	else
		return (ERROR);
}

int	ft_printf(const char *fmt, ...)
{
	int		ret;
	int		i;
	int		errchk;
	va_list	va;

	va_start(va, fmt);
	i = -1;
	ret = 0;
	while (fmt[++i] != '\0')
	{
		if (fmt[i] != '%')
		{
			ret += write(1, &fmt[i], 1);
			continue ;
		}
		errchk = format_check(fmt[++i], va);
		if (errchk == ERROR)
		{
			ret = ERROR;
			break ;
		}
		ret += errchk;
	}
	va_end(va);
	return (ret);
}
