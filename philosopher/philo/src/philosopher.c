/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:32:28 by jbak              #+#    #+#             */
/*   Updated: 2022/08/29 15:43:15 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_and_exit(t_rules *ru, t_philo **phs, int flag, char *str)
{
	int	idx;

	idx = -1;
	if (flag == USAGE)
	{
		write(2, "usage : ./philo \"number_of_philosopher\" ", 41);
		write(2, "\"time_to_die\" \"time_to_eat time_to_sleep\" ", 43);
		write(2, "[number_of_times_each_philosopher_must_eat]\n", 45);
		return (0);
	}
	if (flag == OTHER)
	{
		write(2, "Error : ", 9);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	destroy_and_free(ru, phs);
	return (0);
}

static void	*thread(void *void_philosopher)
{
	t_philo	*ph;

	ph = (t_philo *)void_philosopher;
	if (ph->id % 2)
		spend_time(0, ph->ru->eat_time);
	while (1)
	{
		if (check_time_to_die(ph))
			break ;
		take_fork(ph);
		eat(ph);
		put_down(ph);
		print_action(ph, SLEEP);
		spend_time(0, ph->ru->sleep_time);
		print_action(ph, THINK);
		if (check_time_to_die(ph))
			break ;
	}
	return (NULL);
}

static int	execution(t_philo *phs)
{
	int	idx;

	idx = -1;
	phs->ru->start_time = timestamp();
	if (pthread_mutex_lock(&(phs->ru->waiting)))
		return (1);
	while (++idx < phs->ru->amount)
	{
		phs[idx].last_meal = timestamp();
		if (pthread_create(&((phs[idx]).thread), NULL, thread, &(phs[idx])) || \
			pthread_detach((phs[idx]).thread))
			return (1);
	}
	return (0);
}

static void	monitoring(t_philo *phs)
{
	int	idx;

	while (1)
	{
		idx = -1;
		while (++idx < phs->ru->amount)
		{
			pthread_mutex_lock(&(phs->ru->ate));
			if (phs[idx].ru->must_eat_cnt > 0 && \
				phs->ru->ate_cnt >= phs->ru->amount)
				print_action(&(phs[idx]), ALL_ATE);
			pthread_mutex_unlock(&(phs->ru->ate));
			if (check_time_to_die(&(phs[idx])))
				break ;
		}
		if (idx < phs->ru->amount)
			break ;
	}
	if (pthread_mutex_lock(&(phs->ru->waiting)))
		return ;
}

int	main(int argc, char **argv)
{
	t_rules	ru;
	t_philo	*phs;

	if (argc != 5 && argc != 6)
		return (free_and_exit(NULL, NULL, USAGE, NULL));
	if (init_rules(&ru, argv))
		return (free_and_exit(&ru, NULL, OTHER, "rules initialize failed."));
	if (init_philos(&ru, &phs))
		return (free_and_exit(&ru, &phs, OTHER, "philo initialize failed."));
	if (execution(phs))
		return (free_and_exit(&ru, &phs, OTHER, "execution failed."));
	monitoring(phs);
	return (free_and_exit(&ru, &phs, VALID, NULL));
}
