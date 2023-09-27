/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:30 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:31 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_dollar_cnt(char *str)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			++cnt;
		++i;
	}
	return (cnt);
}

int	get_strlen_after_dollar(char *str)
{
	int	len;

	len = 0;
	while (str && *str != '$')
		++str;
	if (str && *str == '$')
	{
		str++;
		while ((*str != '$' && *str != ' ' && *str != '~') && *str)
		{
			str++;
			len++;
		}
	}
	return (len);
}
