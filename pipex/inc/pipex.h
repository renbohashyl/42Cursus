/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:08:29 by jbak              #+#    #+#             */
/*   Updated: 2022/09/16 16:51:02 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "defs.h"

//ft_split.c
char	**ft_split(char const *s, char c);
void	*splt_free(char ***split);

//utils.c
char	*get_cmdpath(char *cmd, char **envp);
size_t	ft_strlen(const char *s);

#endif