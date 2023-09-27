/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:54 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:54 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	add_to_buf(char c, t_token_buf *buf)
{
	char	*tmp;

	buf->tok_buf[buf->tok_bufindex++] = c;
	if (buf->tok_bufindex >= buf->tok_bufsize)
	{
		tmp = ft_realloc(buf->tok_buf, buf->tok_bufsize * 2);
		if (!tmp)
		{
			errno = ENOMEM;
			return ;
		}
		buf->tok_buf = tmp;
		buf->tok_bufsize *= 2;
	}
}

t_token	*create_token(char *str)
{
	t_token	*tok;
	char	*next_str;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->text_len = ft_strlen(str);
	next_str = malloc(tok->text_len + 1);
	if (!next_str)
	{
		free(tok);
		return (NULL);
	}
	ft_strcpy(next_str, str);
	tok->text = next_str;
	return (tok);
}

void	free_token(t_token *tok)
{
	if (tok->text)
		free(tok->text);
	free(tok);
}

t_token_buf	*init_tokenize(void)
{
	t_token_buf	*buf;

	buf = malloc(sizeof(t_token_buf));
	if (!buf)
		return (NULL);
	ft_memset(buf, 0, sizeof(t_token_buf));
	buf->tok_bufsize = 1024;
	buf->tok_buf = malloc(buf->tok_bufsize);
	if (!buf->tok_buf)
	{
		free(buf);
		return (NULL);
	}
	buf->tok_bufindex = -1;
	return (buf);
}

t_token	*tokenize(t_src *src)
{
	t_token_buf	*buf;
	t_token		*tok;
	int			err;

	if (!src || !src->buffer || !src->bufsize)
		return (NULL);
	buf = init_tokenize();
	if (!buf)
		return (NULL);
	buf->tok_bufindex = 0;
	buf->tok_buf[0] = '\0';
	err = scanning_data(src, buf);
	if (err < 0)
		return (free_buf(buf));
	if (buf->tok_bufindex == 0)
		return (free_buf(buf));
	if (buf->tok_bufindex >= buf->tok_bufsize)
		buf->tok_bufindex--;
	buf->tok_buf[buf->tok_bufindex] = '\0';
	tok = create_token(buf->tok_buf);
	if (!tok)
		return (NULL);
	tok->src = src;
	free_buf(buf);
	return (tok);
}
