/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:45 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:45 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

size_t	find_closing_quote(char *str)
{
	char	quote;
	size_t	i;

	quote = str[0];
	if (quote != '\'' && quote != '\"')
		return (0);
	i = 0;
	while (++i < (ft_strlen(str)))
	{
		if (str[i] == quote)
		{
			if (str[i - 1] == '\\')
			{
				if (quote != '\'')
					continue ;
			}
			return (i);
		}
	}
	return (0);
}

size_t	find_redirection(char *str)
{
	char	redirec;
	size_t	i;

	redirec = str[0];
	if (redirec != '<' && redirec != '>')
		return (0);
	i = 1;
	if (str[i] == redirec)
	{
		if (str[i + 1] == '>' || (str[i + 1] == '<'))
			return (3);
		return (i + 1);
	}
	return (i);
}

int	search_sigquto(char *str)
{
	int	toggle;

	toggle = 0;
	while (*str)
	{
		if (*str == '\'')
			toggle ^= 1;
		if (toggle == 1 && *str == '$')
			break ;
		++str;
	}
	return (toggle);
}
