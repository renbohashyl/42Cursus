/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:18:53 by jbak              #+#    #+#             */
/*   Updated: 2022/08/29 15:34:51 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

typedef enum exit_status
{
	OTHER,
	USAGE,
	VALID
}	t_exit_status;

typedef enum status
{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIED,
	ALL_ATE
}	t_status;

typedef struct s_rules
{
	int				amount;
	int				time_to_die;
	int				eat_time;
	int				sleep_time;
	int				must_eat_cnt;
	int				ate_cnt;
	int				is_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	timestamp;
	pthread_mutex_t	ate;
	pthread_mutex_t	print;
	pthread_mutex_t	waiting;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				flag;
	int				ate_cnt;
	long long		last_meal;
	t_rules			*ru;
	pthread_t		thread;
}	t_philo;

#endif