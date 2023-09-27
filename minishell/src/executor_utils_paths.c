/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:34 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:34 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*__ft_strjoin__(char const *s1, char const *s2, int option)
{
	char	*str;
	long	cnt;

	cnt = 0;
	str = NULL;
	if (s1 || s2)
		str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (str != (void *)0)
	{
		while (s1 && *s1)
			str[cnt++] = (char)*s1++;
		if (option == PATH && s2 && *s2)
			str[cnt++] = '/';
		while (s2 && *s2)
			str[cnt++] = (char)*s2++;
		str[cnt] = '\0';
	}
	return (str);
}

char	**getpaths(char *path_value)
{
	char	**paths;

	paths = NULL;
	if (path_value)
		paths = ft_split(path_value, ':');
	return (paths);
}

int	ft_access(const char *path)
{
	struct stat	status;

	if (stat(path, &status))
		return (0);
	return (status.st_mode & S_IXUSR);
}

int	shift_after_slash(char *cmd)
{
	size_t	idx;
	size_t	slash;

	idx = -1;
	slash = 0;
	while (cmd && cmd[++idx])
		if (cmd[idx] == '/')
			slash = idx + 1;
	return (slash);
}

char	*get_cmdpath(char *cmd, char *path_value)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	if (shift_after_slash(cmd))
		return (cmd);
	if (path_value == NULL)
		return (NULL);
	paths = getpaths(path_value);
	while (paths[++i])
	{
		path = __ft_strjoin__(paths[i], cmd, PATH);
		if (ft_access(path))
		{
			make_free(&paths);
			return (path);
		}
		free(path);
	}
	make_free(&paths);
	return (NULL);
}
