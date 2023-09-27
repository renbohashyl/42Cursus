/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:28 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:28 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	spc_char_check(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str && str[cnt])
	{
		if ((*str >= 0x21 && *str <= 0x2f) || (*str >= 0x3a && *str <= 0x3b) \
			|| (*str >= 0x3f && *str <= 0x40) || \
			(*str >= 0x5b && *str <= 0x60 && *str != 0x5f) \
			|| (*str >= 0x7b && *str <= 0x7f))
			return (1);
		cnt++;
	}
	return (0);
}

int	export(const char *str, t_env **exist_list)
{
	char	**split;

	if (str == NULL)
		return (print_list(*exist_list, EXPORT));
	else if (spc_char_check(str))
		return ((write(2, "SYNTAX ERROR!\n", 14) & 1) | 1);
	else if (ft_strchr(str, '=') == 0 && find_env_name(*exist_list, str))
		return (0);
	split = ft_split(str, '=');
	push_env(*exist_list, new_env(split));
	make_free(&split);
	return (EXIT_SUCCESS);
}
