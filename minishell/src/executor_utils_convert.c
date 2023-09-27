/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_convert.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:32 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:33 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//restore original stdout and stdin
void	handling_fd(int *fd, int backup_or_dup2)
{
	if (backup_or_dup2 == BACKUP)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
	}
	else if (backup_or_dup2 == DUP)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

//it handles orignal STDIN and filenames_from_input_redriections
void	handling_redirection(const char *str, t_word_type type)
{
	int		fd;
	char	*temp_file;

	fd = -1;
	if (type == TYPE_REDIREC_SIG_IN)
		fd = open(str, O_RDONLY);
	else if (type == TYPE_REDIREC_DOB_IN)
	{
		temp_file = ft_strjoin(".temp_", str);
		fd = open(temp_file, O_RDONLY);
		free(temp_file);
	}
	else if (type == TYPE_REDIREC_SIG_OUT)
		fd = open(str, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else if (type == TYPE_REDIREC_DOB_OUT)
		fd = open(str, O_APPEND | O_CREAT | O_RDWR, 0644);
	dup2(fd, type % 2);
	close(fd);
}

//is there any errors after redirects?
int	redir_check(t_word *word)
{
	t_word	*head;
	int		fd;

	head = word;
	fd = -1;
	while (word)
	{
		if (2 <= word->type && word->type <= 5)
		{
			if (!word->next_word || word->next_word->type != TYPE_FILENAME || \
				word->next_word->data[0] == '\0')
			{
				free_word_tree(head);
				return (((write(2, "SYNTAX ERROR\n", 13)) & 0) | -3);
			}
		}
		word = word->next_word;
	}
	return (fd);
}

void	make_cmd(t_word *word, char ***cmd, int *passed_pipe)
{
	t_cmds	cmds;
	t_word	*tmp;

	ft_memset(&cmds, -1, sizeof(t_cmds));
	tmp = word;
	while (cmds.pc < (*passed_pipe - 1))
	{
		if (tmp->type == TYPE_PIPE)
			cmds.pc++;
		tmp = tmp->next_word;
	}
	while ((tmp) && cmds.pc == (*passed_pipe - 1))
	{
		if ((tmp)->type == TYPE_CMD || (tmp)->type == TYPE_WORD)
			(*cmd)[++(cmds.idx)] = (tmp)->data;
		else if ((tmp)->type == TYPE_FILENAME)
			handling_redirection((tmp)->data, (tmp)->prev_word->type);
		if ((tmp)->type == TYPE_PIPE)
			(*passed_pipe)++;
		tmp = tmp->next_word;
		if (cmds.idx > 0 && (*cmd)[cmds.idx][0] == '\0')
			cmds.idx--;
	}
	(*cmd)[++(cmds.idx)] = NULL;
}
