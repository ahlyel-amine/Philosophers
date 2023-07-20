/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/20 06:03:09 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	_eat(t_philo_single_data *data)
{
	sem_wait(data->lp->forks);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	if (data->lp->philos == 1)
	{
		sleep_job_time(data->lp->tm_die + 2);
		print_msg(data, (data->philo_id << 8) | DEAD, data->lp->time);
	}
	sem_wait(data->lp->forks);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	sem_wait(data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	sem_post(data->lp->catch);
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time(data->lp->tm_eat);
	sem_post(data->lp->forks);
	sem_post(data->lp->forks);
	data->eat_counter++;
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time(data->lp->tm_sleep);
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}

static void	listener(t_philo_single_data *data)
{
	long long	start;

	while (data->eat_counter != data->lp->meals_number)
	{
		sem_wait(data->lp->catch);
		start = get_time();
		if (data->time_to_die < start)
		{
			print_msg(data, (data->philo_id << 8) | DEAD, data->lp->time);
			sem_post(data->lp->catch);
			exit(data->philo_id);
		}
		sem_post(data->lp->catch);
		usleep(100);
	}
	exit(0);
}

static void	routine(t_philo_single_data *data)
{
	pthread_t	thread;

	data->time_to_die = get_time() + data->lp->tm_die;
	pthread_create(&thread, NULL, (void *)listener, data);
	pthread_detach(thread);
	while (0x5ABA)
		_eat(data);
}

void	open_semaphores(t_philo *data)
{
	data->catch = sem_open(SEMAPHORE_CATCH_NAME, O_CREAT | O_EXCL, \
	S_IRUSR | S_IWUSR, 1);
	data->forks = sem_open(SEMAPHORE_FORKS_NAME, O_CREAT | O_EXCL, \
	S_IRUSR | S_IWUSR, data->philos);
	data->dead = sem_open(SEMAPHORE_DEAD_NAME, O_CREAT | O_EXCL, \
	S_IRUSR | S_IWUSR, 1);
	sem_unlink(SEMAPHORE_CATCH_NAME);
	sem_unlink(SEMAPHORE_FORKS_NAME);
	sem_unlink(SEMAPHORE_DEAD_NAME);
}

void	take_forks(t_philo data)
{
	int					i;
	int					status;
	t_philo_single_data	philos[PHILO_MAX];

	open_semaphores(&data);
	data.time = get_time();
	i = -1;
	while (++i < data.philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].lp = &data;
		philos[i].eat_counter = 0;
		philos[i].lp->pid = fork();
		if (philos[i].lp->pid == -1)
			return ;
		if (!philos[i].lp->pid)
			routine(&philos[i]);
	}
	while (data.philos)
	{
		wait(&status);
		if (WEXITSTATUS(status))
			return (killall(philos->lp->philos, philos));
		data.philos--;
	}
}
