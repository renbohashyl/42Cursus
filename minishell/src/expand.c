/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:34 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:35 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*_pre_proc(char *str, t_env *envs)
{
	char	*home;
	char	*path_with_tilde;

	path_with_tilde = NULL;
	if (*str == '~' && *(str + 1) == '\0')
	{
		home = find_env_name(envs, "~");
		path_with_tilde = ft_strjoin(home, ++str);
		free(--str);
		return (path_with_tilde);
	}
	return (str);
}

char	*processing_expand(char *str, t_env *envs)
{
	char	*tmp;
	char	*fixed_str;

	fixed_str = replace_str_to_env_val(str, envs);
	tmp = fixed_str;
	fixed_str = _pre_proc(tmp, envs);
	tmp = ft_calloc(ft_strlen(fixed_str) + 2, 1);
	remove_qutoes(tmp, fixed_str, 0);
	free(fixed_str);
	return (tmp);
}

int	isvalid(char c)
{
	if (c >= '0' && '9' <= c)
		return (1);
	else if (c >= 'a' && 'z' <= c)
		return (1);
	else if (c >= 'A' && 'Z' <= c)
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

t_word	*word_expand(char *str, t_env *envs)
{
	if (!str)
		return (NULL);
	else if (!*str)
		return (make_word(str));
	else
		return (make_word(processing_expand(str, envs)));
}
