/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/19 09:08:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	_eat(t_philo_single_data *data)
{
	print_msg((data->philo_id << 8) | FORK, data->lp->time);
	if (data->lp->philos == 1)
	{
		sleep_job_time(data->lp->tm_die + 2);
		print_msg((data->philo_id << 8) | DEAD, data->lp->time);
	}
	print_msg((data->philo_id << 8) | FORK, data->lp->time);
	sem_wait(data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	data->eat_counter++;
	sem_post(data->lp->catch);
	print_msg((data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time(data->lp->tm_eat);
	print_msg((data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time( data->lp->tm_sleep);
	print_msg((data->philo_id << 8) | THINK, data->lp->time);
}

static void	listener(t_philo_single_data *data)
{
	long long	start;

	while (0x5ABA)
	{
		sem_wait(data->lp->catch);
		start = get_time();
		if (data->time_to_die < start)
		{
			print_msg((data->philo_id << 8) | DEAD, data->lp->time);
			exit(data->philo_id);
		}
		if (data->eat_counter == data->lp->meals_number)
		{
			sem_post(data->lp->catch);
			exit(data->lp->philos + 1);
		}
		sem_post(data->lp->catch);
	}
}

static void	routine(t_philo_single_data *data)
{
	pthread_t	thread;

	if (!(data->philo_id % 2))
		sleep_job_time(data->lp->tm_eat);
	data->time_to_die = get_time() + data->lp->tm_die;
	pthread_create(&thread, NULL, (void *)listener, data);
	pthread_detach(thread);
	while (0x5ABA)  
		_eat(data);
	exit(data->philo_id);
}

int	killed(int dead_id, int nbr_of_philo, int *pids)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		if (i != dead_id)
			kill (pids[i], SIGKILL);
		i++;
	}
	return (1);
}

void take_forks(t_philo data)
{
	int			i;
	int			pids[PHILO_MAX];
	int			status;
	t_philo_single_data philos[PHILO_MAX];

	data.catch = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	data.time = get_time();
	i = 0;
	while (i < data.philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].lp = &data;
		philos[i].eat_counter = 0;
		philos[i].eat_counter = 0;
		philos[i].time_to_die = get_time() + data.tm_die;
		pids[i] = fork();
		if (pids[i] == -1)
		{
			sem_unlink(SEMAPHORE_NAME);
			perror("philo: ");
			return ;
		}
		if (!pids[i])
			routine(&philos[i]);
		i++;
	}
	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == data.philos + 1)
				continue ;
			if (killed(WEXITSTATUS(status), data.philos, pids))
			{
				sem_unlink(SEMAPHORE_NAME);
				return ;
			}
		}
	}
	sem_unlink(SEMAPHORE_NAME);
}
