/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:34:08 by jbak              #+#    #+#             */
/*   Updated: 2022/08/29 15:41:36 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "defs.h"

//init.c
int			init_rules(t_rules *ru, char **argv);
int			init_philos(t_rules *ru, t_philo **phs);
int			print_action(t_philo *ph, t_status status);
void		spend_time(long long start, long long how_long);
long long	timestamp(void);

//behavior.c
void		take_fork(t_philo *ph);
void		eat(t_philo *ph);
void		put_down(t_philo *ph);
int			check_time_to_die(t_philo *ph);
int			destroy_and_free(t_rules *ru, t_philo **phs);

//ftfunctions.c
int			ft_atoi(const char *nptr);
size_t		ft_strlen(char *str);
void		ft_bzero(void *s, size_t len);
void		*ft_calloc(size_t nbyte, size_t size);
void		*ft_memset(void *b, int c, size_t len);

#endif