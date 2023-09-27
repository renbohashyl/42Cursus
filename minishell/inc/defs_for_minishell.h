/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs_for_minishell.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:21:59 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:00 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_FOR_MINISHELL_H
# define DEFS_FOR_MINISHELL_H

/*-----------------------enum-----------------------*/
typedef enum e_errflag
{
	PERROR,
	COMMAND,
	OTHER,
	ENV,
	EXPORT,
	PATH
}	t_errflag;

typedef enum e_pipe
{
	READ,
	WRITE
}	t_pipe;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_VAR
}	t_node_type;

typedef enum e_word_type
{
	TYPE_WORD,
	TYPE_CMD,
	TYPE_REDIREC_SIG_IN,
	TYPE_REDIREC_SIG_OUT,
	TYPE_REDIREC_DOB_IN,
	TYPE_REDIREC_DOB_OUT,
	TYPE_PIPE,
	TYPE_FILENAME,
}	t_word_type;
/*-----------------------enum-----------------------*/

/*----------------------struct-----------------------*/
typedef struct s_env
{
	char			*env_name;
	char			*env_value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	int	idx;
	int	pc;
	int	fd;
}	t_cmds;

typedef struct s_ints
{
	int		idx;
	int		status;
	int		temp_status;
	pid_t	pid;
}	t_ints;

typedef struct s_word
{
	int				word_len;
	int				total_pipe;
	char			*data;
	t_word_type		type;
	struct s_word	*next_word;
	struct s_word	*prev_word;
}	t_word;

typedef struct s_node
{
	int				children;
	char			*value;
	t_node_type		type;
	struct s_node	*first_child;
	struct s_node	*next_sibling;
	struct s_node	*prev_sibling;
}	t_node;

typedef struct s_src
{
	char	*buffer;
	long	bufsize;
	long	cur_pos;
}	t_src;

typedef struct s_token
{
	t_src	*src;
	int		text_len;
	char	*text;
}	t_token;

typedef struct s_token_buf
{
	char	*tok_buf;
	int		tok_bufsize;
	int		tok_bufindex;
}	t_token_buf;
/*----------------------struct-----------------------*/

#endif
