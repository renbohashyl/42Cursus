/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:24 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:24 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include "defs_for_minishell.h"
#include "libft.h"

char	*find_env_name(t_env *envs, const char *str)
{
	while (envs)
	{
		if (ft_strncmp(envs->env_name, str, -1) == 0)
			return (envs->env_value);
		envs = envs->next;
	}
	return (NULL);
}

char	*pre_proc(char *str, t_env *envs)
{
	char	*home;
	char	*path_with_tilde;

	path_with_tilde = NULL;
	if (str == NULL || *str == '\0')
	{
		home = find_env_name(envs, "HOME");
		if (home == NULL)
			write(2, "minishell : cd : HOME not set\n", 31);
		return (home);
	}
	else if (*str == '~')
	{
		home = find_env_name(envs, "~");
		path_with_tilde = ft_strjoin(home, ++str);
		return (path_with_tilde);
	}
	return (str);
}

void	change_old_pwd(t_env *envs, char *cur_dir)
{
	while (envs)
	{
		if (ft_strncmp(envs->env_name, "OLDPWD", -1) == 0)
		{
			free(envs->env_value);
			envs->env_value = cur_dir;
			return ;
		}
		envs = envs->next;
	}
}

int	cd(char *str, t_env *envs)
{
	int		fd;
	char	*replaced;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	replaced = pre_proc(str, envs);
	if (chdir(replaced))
	{
		write(2, "cd : ", 6);
		fd = open(replaced, O_RDONLY);
		if (fd != -1)
			write(2, "not a directory\n", 17);
		else if (opendir(replaced) == NULL)
			write(2, "no such a file or directory\n", 29);
		close(fd);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	change_old_pwd(envs, oldpwd);
	return (EXIT_SUCCESS);
}
