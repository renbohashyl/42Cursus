/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:05 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:06 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_HEREDOC_H
# define OPEN_HEREDOC_H

# include "minishell.h"

void	wait_value_input(const char *data, int fd, t_env *envs);

char	*make_filename(const char *data);

int		expand_redirection(const char *data, t_env *envs);
int		open_heredoc(const char *file_name, const char *data, \
					int fd, t_env *envs);

#endif
