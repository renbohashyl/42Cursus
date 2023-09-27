/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:33 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:33 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_builtin(char **cmd, t_env *envs, int *status)
{
	if (ft_strncmp(cmd[0], "cd", -1) == 0)
		*status = cd(cmd[1], envs);
	else if (ft_strncmp(cmd[0], "env", -1) == 0)
		*status = env(cmd[1], &envs);
	else if (ft_strncmp(cmd[0], "pwd", -1) == 0)
		*status = pwd();
	else if (ft_strncmp(cmd[0], "echo", -1) == 0)
		*status = echo((const char **)cmd);
	else if (ft_strncmp(cmd[0], "unset", -1) == 0)
		*status = unset(cmd[1], &envs);
	else if (ft_strncmp(cmd[0], "export", -1) == 0)
		*status = export(cmd[1], &envs);
	else if (ft_strncmp(cmd[0], "exit", -1) == 0)
		ft_exit(cmd);
	else
		return (0);
	return (1);
}

void	exec_cmd(char **cmd_with_args, t_env *envs)
{
	char	*cmdpath;
	char	*path_value;
	char	**envp;

	if (cmd_with_args[0] == NULL || cmd_with_args[0][0] == '\0')
		exit(0);
	envp = list_to_envp(envs);
	path_value = find_env_name(envs, "PATH");
	cmdpath = get_cmdpath(cmd_with_args[0], path_value);
	cmd_with_args[0] += shift_after_slash(cmd_with_args[0]);
	execve(cmdpath, cmd_with_args, envp);
	if (ft_strchr(cmdpath, '/') || opendir(cmd_with_args[0]))
	{
		write(STDERR_FILENO, "minishell : ", 12);
		write(STDERR_FILENO, cmdpath, ft_strlen(cmdpath));
		if (opendir(cmdpath))
			write(STDERR_FILENO, ": is a directory\n", 17);
		else
			write(STDERR_FILENO, ": Permission denied\n", 20);
		exit(126);
	}
	errmsg(cmd_with_args[0], COMMAND);
	exit(127);
}

pid_t	check_builtin(char **cmd, t_env *envs, pid_t pid, int *status)
{
	if (is_builtin(cmd, envs, status))
		return (-1);
	else
	{
		if (pid != 0)
			pid = fork();
		if (pid == 0)
			exec_cmd(cmd, envs);
	}
	if (pid == 0)
		exit(EXIT_SUCCESS);
	return (pid);
}

pid_t	child_do(char **cmd, t_env *envs, int *flag)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd))
		exit(errmsg("pipe init error", PERROR));
	pid = fork();
	if (pid < 0)
		exit(errmsg("forking fork error", PERROR));
	else if (pid == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		check_builtin(cmd, envs, pid, flag);
	}
	else
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
	}
	return (pid);
}

pid_t	is_last_command(char **cmd, t_env *envs, int flag)
{
	pid_t	pid;
	int		dummy;

	dummy = 0;
	if (flag != 0)
		return (child_do(cmd, envs, &dummy));
	pid = fork();
	if (pid < 0)
		exit(errmsg("forking fork error", PERROR));
	else if (pid == 0)
		check_builtin(cmd, envs, pid, &dummy);
	return (pid);
}
