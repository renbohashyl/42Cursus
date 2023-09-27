/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:10:17 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 19:15:04 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static char	*freeit(char **for_free)
{
	free(*for_free);
	*for_free = NULL;
	return (NULL);
}

static void	check_vault(char **f_return, char **vault)
{
	int	i;

	i = 0;
	*f_return = ft_strdup(*vault);
	while ((*vault)[i] && (*vault)[i] != '\n')
		i++;
	*vault = ft_substr(*vault, i + 1, ft_strlen(*vault) - i);
}

static char	*read_and_save(int fd, char *r_buf, char *vault)
{
	ssize_t	read_size;

	read_size = 1;
	while (ft_strchr(vault, '\n') == NULL && read_size)
	{
		read_size = read(fd, r_buf, BUFFER_SIZE);
		if (read_size == -1)
			return (freeit(&r_buf));
		r_buf[read_size] = '\0';
		vault = ft_strjoin(vault, r_buf);
		if (vault == NULL || (read_size == 0 && !*r_buf && !*vault))
		{
			free(r_buf);
			r_buf = NULL;
			if (vault != NULL)
				return (freeit(&vault));
		}
	}
	free(r_buf);
	r_buf = NULL;
	return (vault);
}

char	*get_next_line(int fd)
{
	static char	*vault[4096];
	char		*r_buf;
	char		*f_return;

	f_return = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4096)
		return (NULL);
	r_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (r_buf == NULL)
		return (NULL);
	vault[fd] = read_and_save(fd, r_buf, vault[fd]);
	if (vault[fd] == NULL)
		return (NULL);
	check_vault(&f_return, &vault[fd]);
	if (f_return == NULL)
	{
		free(vault[fd]);
		vault[fd] = NULL;
	}
	return (f_return);
}
