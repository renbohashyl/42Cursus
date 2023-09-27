/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:40 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:41 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_heredoc.h"

static char	*_replace_str_to_env_val(char *data, t_env *env)
{
	char	*tmp;
	int		idx;
	int		cnt;

	cnt = get_dollar_cnt(data);
	if (cnt == 0)
		return (data);
	idx = 0;
	while (cnt--)
	{
		idx = get_strlen_after_dollar(data);
		tmp = ft_calloc(ft_strlen(data) + 1, 1);
		data = cpy_env_val(tmp, data, idx, env);
	}
	return (data);
}

void	wait_value_input(const char *data, int fd, t_env *envs)
{
	char	*line;
	char	*tmp;
	int		idx;

	idx = 0;
	tmp = 0;
	while (1)
	{
		set_signal(HEREDOC);
		line = readline("> ");
		if (line == NULL)
			exit(printf("\033[1A\033[2C") & close(fd));
		else if ((ft_strncmp(line, data, -1) == 0))
			exit(write(fd, "\n", 1) && close(fd));
		write(fd, "\n", (idx > 0) & 1);
		tmp = line;
		line = _replace_str_to_env_val(tmp, envs);
		write(fd, line, ft_strlen(line));
		free(line);
		idx++;
	}
}

int	open_heredoc(const char *file, const char *data, int fd, t_env *envs)
{
	pid_t	pid;
	int		status;

	pid = fork();
	set_signal(CUSTOM);
	if (pid < 0)
		exit(errmsg("forking fork error!", OTHER));
	else if (pid == 0)
		wait_value_input(data, fd, envs);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			write(1, "\b\b  \b\b", 6);
			if (WTERMSIG(status) == SIGINT)
			{
				close(fd);
				fd = open(file, O_RDWR | O_TRUNC, 0644);
				return (close(fd) - 1);
			}
		}
	}
	return (0);
}

char	*make_filename(const char *data)
{
	char	*file_name;
	char	*tmp;

	file_name = ft_strdup(".temp_");
	if (!file_name)
		return (NULL);
	tmp = file_name;
	file_name = ft_strjoin(tmp, data);
	if (!file_name)
		return (NULL);
	free(tmp);
	return (file_name);
}

int	expand_redirection(const char *data, t_env *envs)
{
	int		fd;
	char	*file_name;

	if (ft_strncmp(data, ">", 1) == 0 || ft_strncmp(data, "<", 1) == 0)
		return (-1);
	file_name = make_filename(data);
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0600);
	if (open_heredoc(file_name, data, fd, envs))
	{
		unlink(file_name);
		free(file_name);
		return (-1);
	}	
	free(file_name);
	close(fd);
	return (0);
}
