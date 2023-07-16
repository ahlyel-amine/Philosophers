/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:13 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/16 03:24:39 by aahlyel          ###   ########.fr       */
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
	data->eat_counter++;
	data->time_to_die = get_time() + data->lp->tm_die;
	pthread_mutex_unlock(&data->lp->catch);
	print_msg(data, (data->philo_id << 8) | EAT, data->lp->time);
	sleep_job_time( data->lp->tm_eat);
	pthread_mutex_unlock(&data->left);
	pthread_mutex_unlock(data->right);
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time( data->lp->tm_sleep);
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
	// pthread_mutex_lock(&data->lp->catch);
	// data->eating = false;
	// pthread_mutex_unlock(&data->lp->catch);
}

// void	_sleep(t_philo_single_data *data)
// {
// }

// void	_think(t_philo_single_data *data)
// {
// }