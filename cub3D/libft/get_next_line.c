/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:42:33 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 18:37:24 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define OFF 0
#define ON 1
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*make_it_free(char **for_free)
{
	free(*for_free);
	*for_free = NULL;
	return (NULL);
}

void	check_vault(char **f_return, char **vault)
{
	int	i;

	i = 0;
	while ((*vault)[i] && (*vault)[i] != '\n')
		i++;
	*f_return = ft_substr(vault, 0, i, OFF);
	*vault = ft_substr(vault, i + 1, ft_strlen(*vault) - i, ON);
}

char	*read_and_save(int fd, char *r_buf, char *vault)
{
	ssize_t	read_size;

	read_size = 1;
	while (ft_strchr(vault, '\n') == NULL && read_size)
	{
		read_size = read(fd, r_buf, BUFFER_SIZE);
		if (read_size == -1)
			return (make_it_free(&r_buf));
		r_buf[read_size] = '\0';
		vault = ft_strjoin(&vault, r_buf, ON);
		if (vault == NULL || (read_size == 0 && !*r_buf && !*vault))
		{
			make_it_free(&r_buf);
			if (vault != NULL)
				return (make_it_free(&vault));
		}
	}
	make_it_free(&r_buf);
	return (vault);
}

char	*get_next_line(int fd)
{
	static char	*vault;
	char		*r_buf;
	char		*f_return;

	f_return = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (r_buf == NULL)
		return (NULL);
	vault = read_and_save(fd, r_buf, vault);
	if (vault == NULL)
		return (NULL);
	check_vault(&f_return, &vault);
	if (f_return == NULL)
		make_it_free(&vault);
	return (f_return);
}
