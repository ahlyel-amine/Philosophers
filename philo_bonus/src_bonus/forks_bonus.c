/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/17 05:12:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	_eat(t_philo_single_data *data)
{
	sem_wait(&data->left);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	if (data->lp->philos == 1)
	{
		sleep_job_time(data->lp->tm_die + 2);
		sem_post(&data->left);
		return ;
	}
	sem_wait(data->right);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	sem_wait(&data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	data->eat_counter++;
	sem_post(&data->lp->catch);
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time( data->lp->tm_eat);
	sem_post(&data->left);
	sem_post(data->right);
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time( data->lp->tm_sleep);
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}

static int	watch_philo(t_philo_single_data *data, long long start)
{
	sem_wait(&data->lp->catch);
	if (data->lp->dead)
		return (sem_post(&data->lp->catch), 1);
	if (start > data->time_to_die)
	{
		printf("%lld philo %d is dead\n", get_time() - data->lp->time, data->philo_id);
		data->lp->dead = true;
		return (sem_post(&data->lp->catch), 1);
	}
	if (!data->eaten && data->lp->meals_number != -1 && data->eat_counter == data->lp->meals_number)
	{
		data->eaten = true;
		data->lp->philo_eaten_nbr_meals += 1;
	}
	if (data->lp->meals_number != -1 && data->lp->philo_eaten_nbr_meals == data->lp->philos)
	{
		data->lp->dead = true;
		return (sem_post(&data->lp->catch), 1);
	}
	if (data->lp->dead)
		return (sem_post(&data->lp->catch), 1);
	sem_post(&data->lp->catch);
	return (0);
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
				return ;
			i++;
		}
		usleep(100);
	}
}

static void	routine(t_philo_single_data *data)
{
	if (!(data->philo_id % 2))
		sleep_job_time(data->lp->tm_eat);
	sem_wait(&data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	while (!data->lp->dead)  
	{
		sem_post(&data->lp->catch);
		_eat(data);
		sem_wait(&data->lp->catch);
	}
	sem_post(&data->lp->catch);
}

void take_forks(t_philo_single_data *philos, t_philo data)
{
	int			i;
	int			pids[PHILO_MAX];
	
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
		pids[i] = fork();
		if (!pids[i])
			routine(&philos[i]);
		// pthread_create(&threads[i], NULL, (void *)routine, &(philos[i]));
		i++;
	}
	i = 0;
	listener(philos, data.philos);
	while (i < data.philos)
		waitpid(pids[i], NULL, 0);
	// pthread_mutex_destroy(&data.catch);
	// i = 0;
	// while (i < data.philos)
		// pthread_mutex_destroy(&philos[i++].left);
}
