/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:02 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:02 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "node.h"
# include "scanner.h"
# include "defs_for_minishell.h"

t_word	*make_word(char *str);
t_word	*word_expand(char *str, t_env *envs);
t_word	*lexer_word(t_node *node, t_env *env);

void	remove_qutoes(char *s1, char *s2, int toggle);

int		add_each_word(t_word *prev, t_word *next, t_env *env);
int		get_strlen_after_dollar(char *str);
int		isvalid(char c);
int		select_val_case(char *str, int len);
int		get_dollar_cnt(char *str);

char	*search_env(char *target, t_env *env);
char	*cpy_env_val(char *dst, char *src, int idx, t_env *env);
char	*replace_str_to_env_val(char *str, t_env *env);

#endif
