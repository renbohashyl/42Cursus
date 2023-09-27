/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:26 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:27 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_whitespace(const char *str)
{
	int	cnt;

	if (!str)
		return (0);
	cnt = 0;
	while (((str[cnt] >= 0x09 && str[cnt] <= 0x0D) || str[cnt] == 0x20) \
			&& str[cnt] != '\0')
		cnt++;
	return (cnt);
}

int	check_valid(int status)
{
	int	cnt;

	cnt = 0;
	while (status > 0)
	{
		status /= 10;
		cnt++;
	}
	return (cnt);
}

int	non_numeric(const char *str)
{
	write(2, "minishell : exit: ", 18);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	return (255);
}

void	ft_exit(char **cmd)
{
	int		status;
	char	*str;

	status = 0;
	if (cmd[2] != NULL)
		exit((write(2, "minishell : exit : too many arguments\n", 38) & 1) | 1);
	str = cmd[1];
	str += skip_whitespace(str);
	if (*str >= '0' && *str <= '9')
		status = ft_atoi(str);
	str += check_valid(status);
	if (*str != '\0')
		str += skip_whitespace(str);
	if (*str != '\0')
		exit(non_numeric(str));
	exit(status);
}
