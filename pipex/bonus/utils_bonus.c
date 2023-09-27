/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:30:47 by jbak              #+#    #+#             */
/*   Updated: 2022/09/15 20:26:58 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0 || (*s1 == '\n' && *s2 == '\0'))
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_strjoin(char const *s1, char const *s2, int option)
{
	char	*str;
	long	cnt;

	cnt = 0;
	str = NULL;
	if (s1 || s2)
		str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
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

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (s)
		while (s[cnt])
			cnt++;
	return (cnt);
}

static char	**getpaths(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp && envp[i])
		path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*get_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	if (!ft_strncmp(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	paths = getpaths(envp);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd, PATH);
		if (!access(path, X_OK))
		{
			splt_free(&paths);
			return (path);
		}
		free(path);
	}
	splt_free(&paths);
	return (NULL);
}
