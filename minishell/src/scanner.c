/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:44 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:45 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

int	edit_data_space(char delim, t_src *src, t_token_buf *buf)
{
	if (delim == ' ' || delim == '\t')
	{
		if (buf->tok_bufindex > 0)
			return (1);
	}
	else if (delim == '\n')
	{
		if (buf->tok_bufindex > 0)
			unget_char(src);
		else
			add_to_buf(delim, buf);
		return (1);
	}
	return (0);
}

int	edit_data_redirec(char delim, t_src *src, t_token_buf *buf)
{
	int	i;

	i = 0;
	if (buf->tok_bufindex > 0)
		src->cur_pos--;
	else
	{
		add_to_buf(delim, buf);
		i = find_redirection(src->buffer + src->cur_pos);
		if (i == 3)
		{
			write(2, "syntax error near unexpected token ", 35);
			write(2, &delim, 1);
			write(2, "\n", 1);
			return (-1);
		}
		while (--i)
			add_to_buf(next_char(src), buf);
	}
	return (1);
}

int	edit_data_pipe(char delim, t_src *src, t_token_buf *buf)
{
	if (buf->tok_bufindex > 0)
		src->cur_pos--;
	else if (src->cur_pos == 0 || *(src->buffer + src->cur_pos + 1) != ' ')
	{
		write(2, "syntax error unexpected token ", 30);
		write(2, &delim, 1);
		write(2, "\n", 1);
		return (-1);
	}
	else
		add_to_buf(delim, buf);
	return (1);
}

int	edit_data_quto(char delim, t_src *src, t_token_buf *buf)
{
	int	i;

	i = 0;
	add_to_buf(delim, buf);
	i = find_closing_quote(src->buffer + src->cur_pos);
	if (!i)
	{
		write(2, "error: missing closing quote ", 29);
		write(2, &delim, 1);
		write(2, "\n", 1);
		return (-1);
	}
	while (i--)
		add_to_buf(next_char(src), buf);
	return (0);
}

int	scanning_data(t_src *src, t_token_buf *buf)
{
	int		endpoint;
	char	tmp;

	tmp = next_char(src);
	if (tmp == ERRCHAR || tmp == EOF)
		return (-1);
	endpoint = 0;
	while (tmp != EOF && (endpoint == 0))
	{	
		if (tmp == ' ' || tmp == '\t' || tmp == '\n')
			endpoint = edit_data_space(tmp, src, buf);
		else if (tmp == '>' || tmp == '<')
			endpoint = edit_data_redirec(tmp, src, buf);
		else if (tmp == '|')
			endpoint = edit_data_pipe(tmp, src, buf);
		else if (tmp == '\"' || tmp == '\'')
			endpoint = edit_data_quto(tmp, src, buf);
		else
			add_to_buf(tmp, buf);
		if (endpoint == 0)
			tmp = next_char(src);
	}
	if (endpoint < 0)
		return (-1);
	return (0);
}
