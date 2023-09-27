/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:53:11 by jbak              #+#    #+#             */
/*   Updated: 2022/09/16 16:51:01 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	errmsg(char *str, int flag)
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

static void	child_do(char *cmd, char **envp, int fdin)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd))
		exit(errmsg("pipe error", PERROR));
	pid = fork();
	if (pid < 0)
		exit(errmsg("forking fork error", PERROR));
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], WRITE);
		if (fdin == STDIN_FILENO)
			exit(EXIT_SUCCESS);
		else
			exec_cmd(cmd, envp);
	}
	else
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], READ);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	ffd[2];
	int	cur_cmd_nbr;

	if (argc >= 5)
	{
		cur_cmd_nbr = check_here_doc(argc, argv, ffd);
		dup2(ffd[IN], IN);
		dup2(ffd[OUT], OUT);
		if (cur_cmd_nbr != HEREDOC)
			child_do(argv[++cur_cmd_nbr], envp, ffd[IN]);
		while (cur_cmd_nbr < argc - 2)
			child_do(argv[cur_cmd_nbr++], envp, WRITE);
		exec_cmd(argv[cur_cmd_nbr], envp);
	}
	else
		return (errmsg("Invalid arguments number", OTHER));
	return (0);
}
