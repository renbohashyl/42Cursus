/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:21:04 by jbak              #+#    #+#             */
/*   Updated: 2022/08/29 15:43:46 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print_action(t_philo *ph, t_status status)
{
	long long	cur_t;

	pthread_mutex_lock(&(ph->ru->print));
	cur_t = timestamp();
	if (status == ALL_ATE || status == DIED)
		++(ph->ru->is_died);
	if (status == ALL_ATE)
		printf("Finished!\n");
	else
		printf("%lld ms\t%d ", (cur_t - ph->ru->start_time), ph->id + 1);
	if (status == TAKE)
		printf("has taken a fork\n");
	else if (status == EAT)
		printf("is eating\n");
	else if (status == SLEEP)
		printf("is sleeping\n");
	else if (status == THINK)
		printf("is thinking\n");
	else if (status == DIED)
		printf("is died\n");
	if (status == ALL_ATE || status == DIED)
		pthread_mutex_unlock(&(ph->ru->waiting));
	pthread_mutex_unlock(&(ph->ru->print));
	return (0);
}

void	spend_time(long long start, long long how_long)
{
	long long	cur_t;

	if (start == 0)
		start = timestamp();
	while (1)
	{
		cur_t = timestamp();
		if (cur_t - start >= how_long)
			break ;
		usleep(100);
	}
}

int	init_rules(t_rules *ru, char **argv)
{
	int	idx;

	idx = -1;
	ft_memset(ru, 0, sizeof(t_rules));
	ru->amount = ft_atoi(argv[1]);
	ru->time_to_die = ft_atoi(argv[2]);
	ru->eat_time = ft_atoi(argv[3]);
	ru->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		ru->must_eat_cnt = ft_atoi(argv[5]);
	ru->forks = ft_calloc(sizeof(pthread_mutex_t), ru->amount);
	while (++idx < ru->amount)
		if (pthread_mutex_init(&(ru->forks[idx]), NULL))
			return (1);
	if (pthread_mutex_init(&(ru->print), NULL) || \
		pthread_mutex_init(&(ru->waiting), NULL) || \
		pthread_mutex_init(&(ru->ate), NULL) || \
		pthread_mutex_init(&(ru->timestamp), NULL))
		return (1);
	return (0);
}

int	init_philos(t_rules *ru, t_philo **phs)
{
	int		idx;

	idx = -1;
	(*phs) = ft_calloc(sizeof(t_philo), ru->amount + 1);
	if (!(*phs))
		return (1);
	while (++idx < ru->amount)
	{
		(*phs)[idx].id = idx;
		(*phs)[idx].left_fork = idx;
		(*phs)[idx].right_fork = (idx + 1) % (ru->amount);
		(*phs)[idx].ru = ru;
	}
	return (0);
}
