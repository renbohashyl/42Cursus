/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:01 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:01 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

# define BACKUP 0
# define DUP 1

int		errmsg(const char *str, int flag);
int		shift_after_slash(char *cmd);
int		executor(t_node *node, t_env *envs);
int		is_builtin(char **cmd, t_env *envs, int *status);
int		redir_check(t_word *word);
int		ft_access(const char *path);

pid_t	check_builtin(char **cmd, t_env *envs, pid_t pid, int *status);
pid_t	is_last_command(char **cmd, t_env *envs, int flag);

char	*get_cmdpath(char *cmd, char *path_value);

void	make_cmd(t_word *word, char ***cmd, int *asdf);
void	handling_fd(int *fd, int backup_or_dup2);
void	temp_file_delete(t_word *word);

#endif
