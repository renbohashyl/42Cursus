/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:53:11 by jbak              #+#    #+#             */
/*   Updated: 2022/09/16 17:00:24 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	errmsg(char *str, int flag)
{
	if (flag == PERROR)
		perror(str);
	else if (flag == COMMAND)
	{
		write(STDOUT_FILENO, "pipex : command not found : ", 29);
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (flag == OTHER)
	{
		write(STDOUT_FILENO, "Error : ", 9);
		write(STDOUT_FILENO, str, ft_strlen(str));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (EXIT_FAILURE);
}

static int	shift_after_slash(char *cmd)
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

static void	exec_cmd(char *cmd_from_argv, char **envp)
{
	char	**cmd_with_args;
	char	*cmdpath;

	cmd_with_args = ft_split(cmd_from_argv, ' ');
	cmd_with_args[0] += shift_after_slash(cmd_with_args[0]);
	cmdpath = get_cmdpath(cmd_with_args[0], envp);
	execve(cmdpath, cmd_with_args, envp);
	errmsg(cmd_with_args[0], COMMAND);
	splt_free(&cmd_with_args);
	exit(EXIT_FAILURE);
}

static void	child_do(char *cmd, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd))
		exit(errmsg("pipe error", PERROR));
	pid = fork();
	if (pid < 0)
		exit(errmsg("forking fork error\n", OTHER));
	if (pid == 0)
	{
		close(pipe_fd[IN]);
		dup2(pipe_fd[OUT], OUT);
		exec_cmd(cmd, envp);
	}
	else
	{
		close(pipe_fd[OUT]);
		dup2(pipe_fd[IN], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	file_fd[2];
	int	status;

	if (argc != 5)
		errmsg("usage : ./pipex infile cmd1 cmd2 outfile\n", OTHER);
	file_fd[IN] = open(argv[1], O_RDONLY);
	if (file_fd[IN] < 0)
		exit(errmsg(argv[1], PERROR));
	file_fd[OUT] = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, RWRR);
	if (file_fd[OUT] < 0)
		exit(errmsg(argv[argc - 1], PERROR));
	dup2(file_fd[IN], IN);
	dup2(file_fd[OUT], OUT);
	child_do(argv[2], envp);
	exec_cmd(argv[3], envp);
	wait(&status);
	wait(&status);
	return (0);
}
