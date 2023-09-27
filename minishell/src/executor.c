/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:31 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:32 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	errmsg(const char *str, int flag)
{
	if (flag == PERROR)
		perror(str);
	else if (flag == COMMAND)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": command not found", 20);
		write(STDERR_FILENO, "\n", 1);
	}
	else if (flag == OTHER)
	{
		write(STDERR_FILENO, "Error : ", 9);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
	}
	return (EXIT_FAILURE);
}

//delete the .temp_REDIRECTED_FILE_NAME
void	temp_file_delete(t_word *word)
{
	char	*temp_file;

	while (word)
	{
		if (word->type == TYPE_REDIREC_DOB_IN)
		{
			temp_file = ft_strjoin(".temp_", word->next_word->data);
			unlink(temp_file);
			free(temp_file);
		}
		word = word->next_word;
	}
}

//free (char **), wait child processes and return exit status
int	proc_status(t_ints *in, char **cmd, int *fd)
{
	int	status;
	int	tmp_idx;

	tmp_idx = -1;
	while (++tmp_idx < in->idx)
		if (in->pid == waitpid(-1, &(in->temp_status), 0))
			status = in->temp_status;
	free(cmd);
	handling_fd(fd, DUP);
	set_signal(CUSTOM);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

//check pipeline, and builtin
int	do_pipe_or_builtin(t_word *word, t_env *envs, int *fd, int size)
{
	static t_ints	in;
	const int		pp_cnt = word->total_pipe;
	int				passed_pipe;
	char			**cmd;

	cmd = malloc(sizeof(char *) * (size + 1));
	in.idx = -1;
	in.status = 1;
	passed_pipe = 0;
	handling_fd(fd, BACKUP);
	while (++in.idx <= pp_cnt || (in.idx == 0 && pp_cnt == 0))
	{
		ft_memset(cmd, 0, sizeof(char *) * (size + 1));
		make_cmd(word, &cmd, &passed_pipe);
		if (pp_cnt > 0)
			in.pid = is_last_command(cmd, envs, in.idx - pp_cnt);
		else if (pp_cnt == 0)
			in.pid = check_builtin(cmd, envs, 1, &in.temp_status);
	}
	return (proc_status(&in, cmd, fd));
}

//do commands
int	executor(t_node *node, t_env *envs)
{
	int		status;
	t_word	*word;
	int		fd[2];
	int		node_cnt;

	if (!node || !node->first_child)
		return (1);
	word = lexer_word(node->first_child, envs);
	node_cnt = node->children;
	free_node_tree(node);
	fd[0] = redir_check(word);
	if (fd[0] == -3 || !word)
		return ((fd[0] == -3 * (258)) + word == NULL);
	status = do_pipe_or_builtin(word, envs, fd, node_cnt);
	temp_file_delete(word);
	free_word_tree(word);
	return (status);
}
