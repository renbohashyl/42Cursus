/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:41:40 by jbak              #+#    #+#             */
/*   Updated: 2022/09/15 21:11:04 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	here_doc_do(int argc, char **argv, int *pipe_fd)
{
	char	*gnl;
	pid_t	pid;

	if (argc != 6)
		exit(errmsg("here_doc invalid arguments count", OTHER));
	pid = fork();
	if (pid < 0)
		exit(errmsg("forking fork error!", OTHER));
	while (pid == 0)
	{
		gnl = get_next_line(READ);
		if (gnl == NULL || (ft_strncmp(gnl, argv[2], -1) == 0))
			exit(close(pipe_fd[WRITE]) || close(pipe_fd[READ]));
		write(pipe_fd[WRITE], gnl, ft_strlen(gnl));
		free(gnl);
	}
	if (pid > 0)
	{
		dup2(pipe_fd[READ], READ);
		close(pipe_fd[WRITE]);
		close(pipe_fd[READ]);
		wait(NULL);
	}
}

int	check_here_doc(int argc, char **argv, int *ffd)
{
	int	pipe_fd[2];

	if (ft_strncmp(argv[1], "here_doc", -1) == 0)
	{
		if (pipe(pipe_fd))
			exit(errmsg("pipe error", PERROR));
		ffd[OUT] = open(argv[argc - 1], O_RDWR | O_APPEND | O_CREAT, RWRR);
		if (ffd[OUT] < 0)
			exit(errmsg(argv[argc - 1], PERROR));
		here_doc_do(argc, argv, pipe_fd);
		close(pipe_fd[WRITE]);
		return (HEREDOC);
	}
	else
	{
		ffd[IN] = open(argv[1], O_RDONLY);
		if (ffd[IN] < 0)
			exit(errmsg(argv[1], PERROR));
		ffd[OUT] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (ffd[OUT] < 0)
			exit(errmsg(argv[argc - 1], PERROR));
	}
	return (1);
}
