/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:06 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:08 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"
# include "node.h"
# include "lexer.h"
# include "defs_for_minishell.h"
# include "minishell.h"

# define EXIT_SUCESS 1
# define EXIT_FALIURE -2

int		parse_and_execute(t_src *src, t_env *envs);
t_node	*parse_simple_command(t_token *tok);
t_node	*connect_command(t_token *tok, t_src *src, t_node *cmd);

#endif
