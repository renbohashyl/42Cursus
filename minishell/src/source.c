/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:52 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:53 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	unget_char(t_src *src)
{
	if (src->cur_pos < 0)
		return ;
	src->cur_pos--;
}

char	next_char(t_src *src)
{
	char	c;

	c = 0;
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	if (src->cur_pos == INIT_SRC_POS)
		src->cur_pos = -1;
	else
		c = src->buffer[src->cur_pos];
	if (++src->cur_pos >= src->bufsize)
	{
		src->cur_pos = src->bufsize;
		return (EOF);
	}
	c = (char)c;
	return (src->buffer[src->cur_pos]);
}

char	peek_char(t_src *src)
{
	long	pos;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	pos = src->cur_pos;
	if (pos == INIT_SRC_POS)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (EOF);
	return (src->buffer[pos]);
}

void	skip_white_spaces(t_src *src)
{
	char	c;

	if (!src || !src->buffer)
		return ;
	c = peek_char(src);
	while ((c != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
		c = peek_char(src);
	}
}
