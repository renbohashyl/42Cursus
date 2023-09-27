/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:29 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:30 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	unset(const char *str, t_env **envs)
{
	t_env	*head;
	t_env	*temp;

	head = (*envs);
	if (str == NULL || (ft_strlen(str) == 1 && *str == ' '))
		return (EXIT_SUCCESS);
	else if (envs == NULL || (*envs) == NULL)
		return (((write(2, "wrong! env variable isn't arrived\n", 35)) & 1) | 1);
	else if (spc_char_check(str))
		return ((write(2, "SYNTAX ERROR!\n", 14) & 1) | 1);
	while ((*envs) != NULL)
	{
		if (ft_strncmp((*envs)->env_name, str, -1) == 0)
		{
			temp->next = delete_env(envs);
			(*envs) = temp;
			break ;
		}
		temp = (*envs);
		(*envs) = (*envs)->next;
	}
	(*envs) = head;
	return (EXIT_SUCCESS);
}
