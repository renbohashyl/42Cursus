/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_list_to_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:20 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:22 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*increase_shell_level(char *s2)
{
	int	shell_level;

	shell_level = ft_atoi(s2) + 1;
	free(s2);
	return (ft_itoa(shell_level));
}

static char	*__ft_strjoin(const char *s1, char *s2)
{
	char	*str;
	long	cnt;

	cnt = 0;
	if (ft_strncmp(s1, "SHLVL", -1) == 0)
		s2 = increase_shell_level(s2);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (str != (void *)0)
	{
		while (s1 && *s1)
			str[cnt++] = (char)*s1++;
		str[cnt++] = '=';
		while (s2 && *s2)
			str[cnt++] = (char)*s2++;
		str[cnt] = '\0';
	}
	return (str);
}

char	**list_to_envp(t_env *envs)
{
	t_env	*temp;
	char	**envp;
	size_t	cnt;

	cnt = 0;
	temp = envs;
	while (temp && ++cnt)
		temp = temp->next;
	envp = malloc(sizeof(char *) * (cnt + 1));
	cnt = 0;
	while (envs)
	{
		envp[cnt] = __ft_strjoin(envs->env_name, envs->env_value);
		envs = envs->next;
		cnt++;
	}
	envp[cnt] = NULL;
	return (envp);
}
