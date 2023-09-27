/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:24 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:25 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	compare(const char *haystack, const char *needle)
{
	size_t	hay_cnt;
	size_t	nee_cnt;

	hay_cnt = 0;
	nee_cnt = 0;
	if (!haystack || !needle)
		return (-1);
	while (haystack[hay_cnt])
	{
		nee_cnt = 0;
		if (haystack[hay_cnt] == needle[nee_cnt])
			while (haystack[hay_cnt + nee_cnt] && \
					haystack[hay_cnt + nee_cnt] == needle[nee_cnt])
				nee_cnt++;
		if (haystack[hay_cnt + nee_cnt] == ' ' && needle[nee_cnt] == '\0')
			return (nee_cnt + 1);
		else if (haystack[hay_cnt + nee_cnt] == needle[nee_cnt])
			return (nee_cnt);
		hay_cnt++;
	}
	return (haystack[hay_cnt + nee_cnt] - needle[nee_cnt]);
}

static size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str && str[cnt])
		cnt++;
	return (cnt);
}

void	write_it_until_null(const char **str, int option)
{
	size_t	idx;

	idx = 1;
	while (str && str[idx + option])
	{
		write(1, " ", 1 & (idx > 1));
		write(1, str[idx + option], ft_strlen(str[idx + option]));
		idx++;
	}
	write(1, "\n", option ^ 1);
}

int	echo(const char **str)
{
	int	option;

	option = compare(str[1], "-n");
	if (0 < option && option <= 3)
		write_it_until_null(str, 1);
	else
		write_it_until_null(str, 0);
	return (0);
}
