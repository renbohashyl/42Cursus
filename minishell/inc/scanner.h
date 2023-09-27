/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:08 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:09 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# define ERRCHAR 0
# define INIT_SRC_POS -2

# include "minishell.h"
# include "libft.h"

char		next_char(t_src *src);
void		unget_char(t_src *src);
char		peek_char(t_src *src);

void		skip_white_spaces(t_src *src);
void		add_to_buf(char c, t_token_buf *buf);
void		free_token(t_token *tok);

t_token		*create_token(char *str);
t_token		*tokenize(t_src *src);
t_token_buf	*init_tokenize(void);

int			scanning_data(t_src *src, t_token_buf *buf);
int			search_sigquto(char *str);
int			edit_data_space(char delim, t_src *src, t_token_buf *buf);
int			edit_data_redirec(char delim, t_src *src, t_token_buf *buf);
int			edit_data_pipe(char delim, t_src *src, t_token_buf *buf);
int			edit_data_quto(char delim, t_src *src, t_token_buf *buf);

size_t		find_redirection(char *str);
size_t		find_closing_quote(char *str);

#endif
