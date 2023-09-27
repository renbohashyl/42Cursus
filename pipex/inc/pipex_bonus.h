/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:08:29 by jbak              #+#    #+#             */
/*   Updated: 2022/09/15 19:56:16 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "defs_bonus.h"

//here_doc_bonus.c
int		check_here_doc(int argc, char **argv, int *ffd);

//pipex_bonus.c
int		errmsg(char *str, int flag);

//utils_bonus.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2, int option);
char	*get_cmdpath(char *cmd, char **envp);

//utils2_bonus.c
int		shift_after_slash(char *cmd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);

//utils3_bonus.c
char	*get_next_line(int fd);

//utils4_bonus.c
char	**ft_split(char const *s, char c);
void	*splt_free(char ***split);

#endif