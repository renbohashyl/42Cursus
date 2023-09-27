/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:03 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:03 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//write, close, getcwd, chdir, unlink
# include <unistd.h>

//stat, lstat, fstat
# include <sys/types.h>
# include <sys/stat.h>

//printf, perror
# include <stdio.h>

//malloc, free
# include <stdlib.h>

//open
# include <fcntl.h>

//errno
# include <errno.h>

//readline functions
# include <readline/readline.h>
# include <readline/history.h>

//opendir
# include <dirent.h>

//signal
# include <signal.h>

//custom defines
# include "defs_for_minishell.h"
# include "lexer.h"
# include "node.h"
# include "scanner.h"
# include "parser.h"
# include "sig.h"
# include "open_heredoc.h"
# include "executor.h"

void	*free_word_tree(t_word *word);

//minishell.c
size_t	skip_whitespace(const char *str);

//list_to_envp.c
char	**list_to_envp(t_env *envs);

//env_to_list.c
t_env	*envp_to_list(const char **envp);
t_env	*delete_env(t_env **node);
t_env	*new_env(char **split);
void	push_env(t_env *list, t_env *new_node);
int		print_list(t_env *list, int flag);

//mergesort_for_linked_list.c
void	mergesort_for_linked_list(t_env **head_ref);

//builtins
int		pwd(void);
int		export(const char *str, t_env **exist_list);
int		echo(const char **str);
int		cd(const char *str, t_env *envs);
int		unset(const char *str, t_env **envs);
int		env(const char *str, t_env **exist_list);
void	ft_exit(char **cmd);

//builtin_cd.c
char	*find_env_name(t_env *envs, const char *str);
char	*pre_proc(const char *str, t_env *envs);

//builtin_export.c
int		spc_char_check(const char *str);

//signal.c
void	sig_handler(int signum);
void	set_signal(int state);
void	pipe_sighandler(int signum);

//free.c
void	*free_buf(t_token_buf *buf);
#endif
