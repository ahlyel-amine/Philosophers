/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/15 10:59:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	catche(t_philo_single_data *data)
{
	long long	start;
	int			i;
	bool		stop;

	stop = false;
			start = get_time();
	while (0x5ABA)
	{
		i = 0;
		while (i < data[0].lp->philos)
		{
			pthread_mutex_lock(&data[0].lp->catch);
			if (!dead && start >= data[0].time_to_die && !data[0].eating)
			{
				dead = 1;
				printf("%lld philo %d is dead\n", get_time() - data[0].lp->time, i + 1);
				stop = true;
				break ;
			}
			else if (dead)
			{
				stop = true;
				break ;
			}
			pthread_mutex_unlock(&data[i].lp->catch);
			i++;
		}
		if (stop)
		{
			pthread_mutex_unlock(&data[i].lp->catch);
			break;
		}
	}
}

static void	*routine(t_philo_single_data *data)
{
	// pthread_t	t;
	if (!(data->philo_id % 2))
		usleep(900);
	data->time_to_die = get_time() + data->lp->tm_die;
	// pthread_create(&t, NULL, (void *)catche, data);
	pthread_mutex_lock(&data->lp->catch);
	while (!dead)  
	{
		pthread_mutex_unlock(&data->lp->catch);
		_eat(data);
		if (data->lp->philos == 1)
			break ;
		_sleep(data);
		_think(data);
		pthread_mutex_lock(&data->lp->catch);
	}
	pthread_mutex_unlock(&data->lp->catch);
	// if (pthread_join(t, NULL))
	// 	return ((void *)1);
	return ((void *)0);
}

void take_forks(t_philo_single_data *philos, t_philo data)
{
	int			i;
	pthread_t	*threads;
	// pthread_t	life_cycle;

	i = 0;
	data.time = get_time();
	threads = malloc(sizeof(pthread_t) * (data.philos + 1));
	if (!threads)
		return ;
	
	philos[0].lp = &data;
	philos[0].eating = false;
	pthread_create(&threads[data.philos], NULL, (void *)catche, philos);
	while (i < data.philos)
	{
		
		philos[i].philo_id = i + 1;
		if (i)
		{
			
		philos[i].lp = &data;
		philos[i].eating = false;
		}
		pthread_create(&threads[i], NULL, (void *)routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < data.philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// if (pthread_join(life_cycle, NULL))
	// 	return ;
	free(threads);
	pthread_mutex_destroy(&data.catch);
	i = 0;
	while (i < data.philos)
		pthread_mutex_destroy(&philos[i++].left);
	free(philos);
}

// void	take_forks(t_philo_single_data *philos, t_philo data)
// {
// 	int	i;
// 	i = 0;
// 	data.time = get_time();
// 	while (i < data.philos)
// 	{
// 		printf("%d\n", i);
// 		philos[i].philo_id = i + 1;
// 		philos[i].lp = &data;
// 		philos[i].eating = false;
// 		pthread_create(philos[i].thread, NULL, (void *)routine, &(philos[i]));
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data.philos)
// 	{	
// 		pthread_join(*(philos[i].thread), NULL);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&data.catch);
// 	i = 0;
// 	while (i < data.philos)
// 		pthread_mutex_destroy(&philos[i++].left);
// 	free(philos);
// }
