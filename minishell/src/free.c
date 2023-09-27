/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:36 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:36 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_buf(t_token_buf *buf)
{
	if (buf->tok_buf)
		free(buf->tok_buf);
	free(buf);
	return (NULL);
}