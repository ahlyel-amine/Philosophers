/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/21 04:16:24 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	_eat(t_philo_single_data *data)
{
	if (pthread_mutex_lock(&data->left))
		return ;
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	if (data->lp->philos == 1)
	{
		sleep_job_time(data->lp->tm_die + 2);
		pthread_mutex_unlock(&data->left);
		return ;
	}
	if (pthread_mutex_lock(data->right))
		return ;
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	if (pthread_mutex_lock(&data->lp->catch))
		return ;
	data->time_to_die = get_time() + data->lp->tm_die;
	data->eat_counter++;
	if (pthread_mutex_unlock(&data->lp->catch))
		return ;
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time(data->lp->tm_eat);
	if (pthread_mutex_unlock(&data->left) || pthread_mutex_unlock(data->right))
		return ;
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time(data->lp->tm_sleep);
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}

static int	watch_philo(t_philo_single_data *data, long long start)
{
	if (pthread_mutex_lock(&data->lp->catch))
		return (1);
	if (data->lp->dead)
		return (pthread_mutex_unlock(&data->lp->catch), 1);
	if (start > data->time_to_die)
	{
		printf("%lld philo %d is dead\n", get_time() - data->lp->time, \
		data->philo_id);
		data->lp->dead = true;
		return (pthread_mutex_unlock(&data->lp->catch), 1);
	}
	if (!data->eaten && data->lp->meals_number != -1 \
	&& data->eat_counter == data->lp->meals_number)
	{
		data->eaten = true;
		data->lp->philo_eaten_nbr_meals += 1;
	}
	if (data->lp->philo_eaten_nbr_meals == data->lp->philos)
	{
		data->lp->dead = true;
		return (pthread_mutex_unlock(&data->lp->catch), 1);
	}
	if (data->lp->dead)
		return (pthread_mutex_unlock(&data->lp->catch), 1);
	return (pthread_mutex_unlock(&data->lp->catch), 0);
}

static void	listener(t_philo_single_data *data, int philos)
{
	long long	start;
	int			i;

	while (0x5ABA)
	{
		start = get_time();
		i = 0;
		while (i < philos)
		{
			if (watch_philo(&data[i], start))
			{
				pthread_mutex_unlock(&data[i].lp->catch);
				return ;
			}
			i++;
		}
		usleep(100);
	}
}

static void	routine(t_philo_single_data *data)
{
	if (!(data->philo_id % 2))
		sleep_job_time(data->lp->tm_eat);
	if (pthread_mutex_lock(&data->lp->catch))
		return ;
	data->time_to_die = get_time() + data->lp->tm_die;
	while (!data->lp->dead)
	{
		if (pthread_mutex_unlock(&data->lp->catch))
			return ;
		_eat(data);
		if (pthread_mutex_lock(&data->lp->catch))
			return ;
	}
	if (pthread_mutex_unlock(&data->lp->catch))
		return ;
}

void	take_forks(t_philo_single_data *philos, t_philo data)
{
	int	i;

	i = 0;
	data.time = get_time();
	data.philo_eaten_nbr_meals = 0;
	while (i < data.philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].lp = &data;
		philos[i].eat_counter = 0;
		philos[i].time_to_die = get_time() + data.tm_die;
		philos[i].eaten = false;
		if (pthread_create(&(philos[i].thread), \
		NULL, (void *)routine, &(philos[i])))
		{
			join_destroy(philos, data, i, data.philos);
			return ;
		}
		i++;
	}
	listener(philos, data.philos);
	join_destroy(philos, data, data.philos, data.philos);
}
