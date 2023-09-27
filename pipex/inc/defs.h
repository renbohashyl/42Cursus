/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:24:01 by jbak              #+#    #+#             */
/*   Updated: 2022/09/16 16:19:51 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

typedef enum e_status
{
	PERROR,
	COMMAND,
	OTHER
}	t_status;

# define IN 0
# define OUT 1
# define NOP 0
# define PATH 1
# define RWRR 0644

#endif