/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/19 08:11:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	_eat(t_philo_single_data *data)
{
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	if (data->lp->philos == 1)
	{
		sleep_job_time(data->lp->tm_die + 2);
		print_msg(data, (data->philo_id << 8) | DEAD, data->lp->time);
	}
	// printf("%d\n", data->philo_id);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	sem_wait(data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	data->eat_counter += 1;
	sem_post(data->lp->catch);
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time(data->lp->tm_eat);
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time( data->lp->tm_sleep);
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}

static void	listener(t_philo_single_data *data, int philos)
{
	long long	start;

	while (0x5ABA)
	{
		// printf("%d try lock\n", data->philo_id);
		sem_wait(data->lp->catch);
		// printf("%d locking\n", data->philo_id);
		// usleep(100);
		start = get_time();
		// printf("%lld %lld %d philo %d\n", data->time_to_die, start, )
		if (data->time_to_die <= start)
		{
			print_msg(data, (data->philo_id << 8) | DEAD, data->lp->time);
			exit(data->philo_id);
		}
		if (data->lp->tm_eat != -1 && data->eat_counter == data->lp->tm_eat)
		{
			
			print_msg(data, (data->philo_id << 8) | DEAD, data->lp->time);
			exit(data->lp->philos + 1);
		}
		// printf("%d unlocking\n", data->philo_id);
		sem_post(data->lp->catch);
		// usleep(1000);
	}
}

static void	routine(t_philo_single_data *data)
{
	int			exit_;
	pthread_t	thread;

	if (data->philo_id % 2)
		usleep(data->lp->tm_eat);
	// 	usleep(100);
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
		if (i != nbr_of_philo)
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

	sem_unlink("/tmp/sem_");
	data.catch = sem_open("/tmp/sem_", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
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
			sem_unlink("/tmp/sem_");
			perror("philo: ");
			return ;
		}
		if (!pids[i])
			routine(&philos[i]);
		// printf("next\n");
		i++;
	}
	i = 0;
	while (wait(&status) != -1)
	{
		if (WEXITSTATUS(status) == data.philos + 1)
			continue ;
		if (killed(WEXITSTATUS(status), data.philos, pids))
		{
			sem_unlink("/tmp/sem_");
			return ;
		}
	}
	sem_unlink("/tmp/sem_");
}
