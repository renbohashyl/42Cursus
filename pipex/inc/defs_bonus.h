/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:24:01 by jbak              #+#    #+#             */
/*   Updated: 2022/09/15 20:16:08 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_BONUS_H
# define DEFS_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef enum e_pipes
{
	READ,
	WRITE
}	t_pipes;

typedef enum e_errflag
{
	PERROR,
	COMMAND,
	OTHER
}	t_errflag;

# define IN 0
# define OUT 1
# define PATH 0
# define NOP 1
# define HEREDOC 3
# define RWRR 0644

#endif