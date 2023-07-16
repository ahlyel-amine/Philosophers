/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/16 08:51:24 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	_eat(t_philo_single_data *data)
{
	pthread_mutex_lock(&data->left);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	pthread_mutex_lock(data->right);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	pthread_mutex_lock(&data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	data->eat_counter++;
	pthread_mutex_unlock(&data->lp->catch);
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time( data->lp->tm_eat);
	pthread_mutex_unlock(&data->left);
	pthread_mutex_unlock(data->right);
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time( data->lp->tm_sleep);
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}

static int	watch_philo(t_philo_single_data *data, long long start)
{
	pthread_mutex_lock(&data->lp->catch);
	if (data->lp->dead)
		return (1);
	if (start > data->time_to_die)
	{
		printf("%lld philo %d is dead\n", get_time() - data->lp->time, data->philo_id);
		data->lp->dead = true;
		return (1);
	}
	if (!data->eaten && data->lp->meals_number != -1 && data->eat_counter == data->lp->meals_number)
	{
		data->eaten = true;
		data->lp->philo_eaten_nbr_meals += 1;
	}
	if (data->lp->meals_number != -1 && data->lp->philo_eaten_nbr_meals == data->lp->philos)
	{
		data->lp->dead = true;
		return (1);
	}
	if (data->lp->dead)
		return (1);
	pthread_mutex_unlock(&data->lp->catch);
	return (0);
}

static void	listener(t_philo_single_data *data, int philos)
{
	long long	start;
	int			i;
	bool		stop;

	stop = false;
	while (0x5ABA)
	{
		start = get_time();
		i = 0;
		while (i < philos)
		{
			if (watch_philo(&data[i], start))
			{
				pthread_mutex_unlock(&data[i].lp->catch);
				stop = true;
				break;
			}
			i++;
		}
		if (stop)
			break ;
		usleep(100);
	}
}

static void	routine(t_philo_single_data *data)
{
	if (!(data->philo_id % 2))
		sleep_job_time(data->lp->tm_eat);
	pthread_mutex_lock(&data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	while (!data->lp->dead)  
	{
		pthread_mutex_unlock(&data->lp->catch);
		_eat(data);
		pthread_mutex_lock(&data->lp->catch);
	}
	pthread_mutex_unlock(&data->lp->catch);
}

void take_forks(t_philo_single_data *philos, t_philo data)
{
	int			i;
	pthread_t	threads[PHILO_MAX];

	i = 0;
	data.time = get_time();
	data.philo_eaten_nbr_meals = 0;
	while (i < data.philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].lp = &data;
		philos[i].eat_counter = 0;
		// philos[i].philo_eaten_nbr_meals = 0;
		philos[i].time_to_die = get_time() + data.tm_die;
		philos[i].eaten = false;
		pthread_create(&threads[i], NULL, (void *)routine, &(philos[i]));
		i++;
	}
	i = 0;
	listener(philos, data.philos);
	while (i < data.philos)
		pthread_join(threads[i++], NULL);
	// pthread_mutex_destroy(&data.catch);
	// i = 0;
	// while (i < data.philos)
		// pthread_mutex_destroy(&philos[i++].left);
}
