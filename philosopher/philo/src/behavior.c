/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:57:51 by jbak              #+#    #+#             */
/*   Updated: 2022/08/29 15:57:45 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *ph)
{
	if (check_time_to_die(ph))
		return ;
	if (pthread_mutex_lock(&(ph->ru->forks[ph->left_fork])) \
		|| print_action(ph, TAKE) || \
		pthread_mutex_lock(&(ph->ru->forks[ph->right_fork])) \
		|| print_action(ph, TAKE))
		pthread_mutex_unlock(&(ph->ru->waiting));
	if (check_time_to_die(ph))
		return ;
}

void	eat(t_philo *ph)
{
	if (check_time_to_die(ph))
		return ;
	pthread_mutex_lock(&(ph->ru->ate));
	pthread_mutex_lock(&(ph->ru->timestamp));
	ph->last_meal = timestamp();
	pthread_mutex_unlock(&(ph->ru->timestamp));
	print_action(ph, EAT);
	pthread_mutex_unlock(&(ph->ru->ate));
	spend_time(ph->last_meal, ph->ru->eat_time);
	pthread_mutex_lock(&(ph->ru->ate));
	(ph->ate_cnt)++;
	if (ph->ate_cnt == ph->ru->must_eat_cnt && !ph->flag)
		ph->flag = 1;
	if (ph->ate_cnt == ph->ru->must_eat_cnt && ph->flag)
		(ph->ru->ate_cnt)++;
	pthread_mutex_unlock(&(ph->ru->ate));
	if (check_time_to_die(ph))
		return ;
}

void	put_down(t_philo *ph)
{
	if (check_time_to_die(ph))
		return ;
	if (pthread_mutex_unlock(&(ph->ru->forks[ph->left_fork])) || \
		pthread_mutex_unlock(&(ph->ru->forks[ph->right_fork])))
		pthread_mutex_unlock(&(ph->ru->waiting));
	if (check_time_to_die(ph))
		return ;
}

int	check_time_to_die(t_philo *ph)
{
	if (pthread_mutex_lock(&(ph->ru->print)) || \
		pthread_mutex_lock(&(ph->ru->timestamp)))
		return (1);
	if (ph->ru->is_died >= 1)
		return (1);
	else if (timestamp() - ph->last_meal >= ph->ru->time_to_die)
	{
		pthread_mutex_unlock(&(ph->ru->timestamp));
		pthread_mutex_unlock(&(ph->ru->ate));
		pthread_mutex_unlock(&(ph->ru->print));
		print_action(ph, DIED);
		return (0);
	}
	if (pthread_mutex_unlock(&(ph->ru->print)) || \
		pthread_mutex_unlock(&(ph->ru->timestamp)))
		return (1);
	return (0);
}

int	destroy_and_free(t_rules *ru, t_philo **phs)
{
	int	idx;

	idx = -1;
	if (ru && ru->forks)
		while (ru->forks && ++idx < ru->amount)
			pthread_mutex_destroy(&(ru->forks[idx]));
	pthread_mutex_destroy(&(ru->print));
	pthread_mutex_destroy(&(ru->waiting));
	pthread_mutex_destroy(&(ru->ate));
	pthread_mutex_destroy(&(ru->timestamp));
	free(ru->forks);
	if (phs && *phs)
		free(*phs);
	return (0);
}
