/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:46 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:51 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*_find_env_name(t_env *envs, const char *str)
{
	char	*trim_target;

	if (!str)
		return (NULL);
	trim_target = ft_strtrim(str, "\"\' ");
	if (!trim_target)
		return (NULL);
	while (envs)
	{
		if (ft_strncmp(envs->env_name, trim_target, -1) == 0)
		{
			free(trim_target);
			return (envs->env_value);
		}
		envs = envs->next;
	}
	free(trim_target);
	return (NULL);
}

static void	*add_dst(char *dst, const char *target)
{
	char	*dst_tmp;

	dst_tmp = ft_strjoin(dst, target);
	if (!dst_tmp)
		return (NULL);
	free(dst);
	dst = NULL;
	return (dst_tmp);
}

char	*cpy_env_val(char *dst, char *src, int idx, t_env *env)
{
	char	*tmp;
	char	*env_tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(src) + 1 + idx);
	while (src[j] != '$' && src[j])
		dst[i++] = src[j++];
	ft_strlcpy(tmp, (src + j + 1), idx + 1);
	if (!tmp)
		return (NULL);
	env_tmp = _find_env_name(env, tmp);
	free(tmp);
	if (env_tmp)
		dst = add_dst(dst, env_tmp);
	if ((src[idx + j + 1]) != '\0')
		dst = add_dst(dst, src + (idx + j + 1));
	if (!dst)
		return (NULL);
	free(src);
	return (dst);
}

char	*replace_str_to_env_val(char *str, t_env *env)
{
	char	*tmp;
	char	*dst;
	int		idx;
	int		cnt;

	tmp = str;
	dst = NULL;
	if (search_sigquto(tmp))
		return (ft_strdup(str));
	else
	{
		cnt = get_dollar_cnt(str);
		if (cnt == 0)
			return (ft_strdup(str));
		idx = 0;
		while (cnt--)
		{
			if (!dst)
				dst = ft_strdup(str);
			idx = get_strlen_after_dollar(dst);
			tmp = ft_calloc(ft_strlen(str) + 1, 1);
			dst = cpy_env_val(tmp, dst, idx, env);
		}
	}
	return (dst);
}
