/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/16 03:30:16 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*catche(t_philo_single_data *data)
{
	long long	start;
	while (0x5ABA)
	{
		start = get_time();
		pthread_mutex_lock(&data->lp->catch);
		if (dead)
			break ;
		if (!dead && start > data->time_to_die/* && !data->eating*/)
		{
			printf("%lld philo %d is dead\n", get_time() - data->lp->time, data->philo_id);
			dead = 1;
			break ;
		}
		if (data->lp->meals_number != -1 && data->eat_counter == data->lp->meals_number)
			data->philo_eaten_nbr_meals++;
		// usleep(1);
		if (data->lp->meals_number != -1 && data->philo_eaten_nbr_meals == data->lp->philos)
		{
			dead = 1;
			break ;
		}
		if (dead)
			break ;
		pthread_mutex_unlock(&data->lp->catch);
		// sleep_job_time(2);
		usleep(100);
	}
	pthread_mutex_unlock(&data->lp->catch);
	return ((void *)0);
}

static void	*routine(t_philo_single_data *data)
{
	pthread_t	t;
	if (!(data->philo_id % 2))
		sleep_job_time( data->lp->tm_eat);
	data->time_to_die = get_time() + data->lp->tm_die;
	pthread_create(&t, NULL, (void *)catche, data);
	pthread_mutex_lock(&data->lp->catch);
	while (!dead)  
	{
		pthread_mutex_unlock(&data->lp->catch);
		_eat(data);
		pthread_mutex_lock(&data->lp->catch);
	}
	pthread_mutex_unlock(&data->lp->catch);
	if (pthread_join(t, NULL))
		return ((void *)1);
	return ((void *)0);
}

void take_forks(t_philo_single_data *philos, t_philo data)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	data.time = get_time();
	threads = malloc(sizeof(pthread_t) * data.philos);
	if (!threads)
		return ;
	while (i < data.philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].lp = &data;
		philos[i].eating = false;
		philos[i].eat_counter = 0;
		philos[i].philo_eaten_nbr_meals = 0;
		pthread_create(&threads[i], NULL, (void *)routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < data.philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
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