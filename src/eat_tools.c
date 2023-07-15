/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:49:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/15 08:51:01 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_fork(t_philo_single_data *data, int fork_)
{
	if (fork_ == LEFT)
		pthread_mutex_lock(&data->left);
	else
		pthread_mutex_lock(data->right);
	print_msg(data, (data->philo_id << 8) | FORK, data->lp->time);
}

static void	drop_forks(t_philo_single_data *data)
{
	pthread_mutex_unlock(&data->left);
	pthread_mutex_unlock(data->right);
}

static void	start_eating(t_philo_single_data *data)
{
	pthread_mutex_lock(&data->lp->catch);
	data->time_to_die = get_time() + data->lp->tm_die;
	data->eating = true;
	pthread_mutex_unlock(&data->lp->catch);
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time(data->lp->tm_eat);
}

static void	finish_eating(t_philo_single_data *data)
{
	pthread_mutex_lock(&data->lp->catch);
	data->eating = false;
	pthread_mutex_unlock(&data->lp->catch);
}

void	_eat(t_philo_single_data *data)
{
	if (dead_check(data))
		return ;
	take_fork(data, LEFT);
	if (data->lp->philos == 1)
	{
		if (!dead_check(data))
			;
		pthread_mutex_unlock(&data->left);
		return ;
	}
	take_fork(data, RIGHT);
	start_eating(data);
	drop_forks(data);
	finish_eating(data);
}
