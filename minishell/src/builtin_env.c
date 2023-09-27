/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:25 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:26 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	env(const char *str, t_env **exist_list)
{
	char	**split;

	if (str == NULL)
		return (print_list(*exist_list, ENV));
	else if (spc_char_check(str))
		return ((write(2, "SYNTAX ERROR!\n", 14) & 1) | 1);
	else if (ft_strchr(str, '=') == 0)
		return (0);
	split = ft_split(str, '=');
	if (split[1] == NULL)
		return ((write(2, "SYNTAX ERROR\n", 14) & EXIT_FAILURE) | 1);
	push_env(*exist_list, new_env(split));
	make_free(&split);
	return (EXIT_SUCCESS);
}
