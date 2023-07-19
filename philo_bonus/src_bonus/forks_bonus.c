/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/19 02:04:39 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	_eat(t_philo_single_data *data)
{
	printf ("child proccess %d  eating \n", data->philo_id);
	usleep(200);	// pthread_mutex_lock(&data->left);
	// print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	// if (data->lp->philos == 1)
	// {
	// 	sleep_job_time(data->lp->tm_die + 2);
	// 	// pthread_mutex_unlock(&data->left);
	// 	return ;
	// }
	// // pthread_mutex_lock(data->right);
	// print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
	// // sem_wait(data->lp->catch);
	// data->time_to_die = get_time() + data->lp->tm_die;
	// data->eat_counter++;
	// // sem_post(data->lp->catch);
	// print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	// sleep_job_time( data->lp->tm_eat);
	// // pthread_mutex_unlock(&data->left);
	// // pthread_mutex_unlock(data->right);
	// print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	// sleep_job_time( data->lp->tm_sleep);
	// print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}

static void	listener(t_philo_single_data *data, int philos)
{
	long long	start;
	int			i;

	for (int i = 0; i < 10; i++)
	{
		start = get_time();
		printf ("Thread %d try to lock \n", data->philo_id);
		sem_wait(data->lp->catch);
		printf ("Thread %d locking \n", data->philo_id);
		// usleep(200);
		printf ("Thread %d unlocking \n", data->philo_id);
		// if (data->lp->dead)
		// {
		// 	sem_post(data->lp->catch);
		// 	return ;
		// }
		// if (start > data->time_to_die)
		// {
		// 	printf("%lld philo %d is dead\n", get_time() - data->lp->time, data->philo_id);
		// 	data->lp->dead = true;
		// 	sem_post(data->lp->catch);
		// 	return ;
		// }
		// if (!data->eaten && data->lp->meals_number != -1 && data->eat_counter == data->lp->meals_number)
		// {
		// 	data->eaten = true;
		// 	data->lp->philo_eaten_nbr_meals += 1;
		// }
		// if (data->lp->meals_number != -1 && data->lp->philo_eaten_nbr_meals == data->lp->philos)
		// {
		// 	data->lp->dead = true;
		// 	return ;
		// }
		// if (data->lp->dead)
		// {
		// 	sem_post(data->lp->catch);
		// 	return ;
		sem_post(data->lp->catch);
		usleep(100);
	}
}

static void	routine(t_philo_single_data *data)
{
	long long	start;
	int			exit_;
	pthread_t	thread;
	data->time_to_die = get_time() + data->lp->tm_die;
	// data->lp->catch = sem_open("semaphore", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	pthread_create(&thread, NULL, (void *)listener, data);

	printf("child process %d try lock\n", data->philo_id);
	sem_wait(data->lp->catch);
	printf("child process %d locking\n", data->philo_id);
	for (int i = 0; i < 10; i++)  
	{
		usleep(100);
		printf ("child process %d unlocking \n", data->philo_id);
		printf("child process %d try lock\n", data->philo_id);
		sem_post(data->lp->catch);
		_eat(data);
		printf ("child process %d unlocking \n", data->philo_id);
		sem_wait(data->lp->catch);
	}
	sem_post(data->lp->catch);
	// printf("alo %d\n", data->philo_id);
	// pthread_detach(thread);
	// printf("alo_ %d\n", data->philo_id);
	exit(exit_);
}

void take_forks(t_philo data)
{
	int			i;
	int			pids[PHILO_MAX];
	t_philo_single_data philos[PHILO_MAX];
	
	i = 0;
	data.time = get_time();
	data.philo_eaten_nbr_meals = 0;
	// sem_t	*semaphore;
	sem_unlink("semaphore");
	// semaphore = sem_open("semaphore", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, 1);
	data.catch = sem_open("semaphore", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	while (i < data.philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].lp = &data;
		philos[i].eat_counter = 0;
		philos[i].time_to_die = get_time() + data.tm_die;
		philos[i].eaten = false;
		pids[i] = fork();
		if (pids[i] == -1)
			exit (1); // ! just for now
		if (!pids[i])
		{
			routine(&philos[i]);
		}
		printf("next\n");
		i++;
		
	}
	i = 0;
	while (i < data.philos)
		waitpid(pids[i], NULL, 0);
	// pthread_mutex_destroy(&data.catch);
	// i = 0;
	// while (i < data.philos)
		// pthread_mutex_destroy(&philos[i++].left);
}
