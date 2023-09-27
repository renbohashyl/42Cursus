/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:50:40 by jbak              #+#    #+#             */
/*   Updated: 2022/03/24 15:54:03 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define DIGIT "0123456789ABCDEF"
# define ERROR -1
# define SMALL 32
# define INT_DIGIT 10
# define ADDR_MAX 8
# define LOWER 1
# define UPPER 0

int	ft_printf(const char *fmt, ...);
int	format_check(char arg, va_list va);
int	prt_char(va_list va);
int	prt_str(va_list va);
int	prt_deci(int nbr);
int	prt_u_deci(unsigned int nbr);
int	prt_hexa(unsigned int nbr, int low_up);
int	prt_addr(unsigned long long nbr);

#endif
