/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:10:30 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/15 04:58:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time()
{
	struct timeval	tv;
	long long	time_;

	gettimeofday(&tv, NULL);
	time_ = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_);
}

void	sleep_job_time(long long sleep_time)
{
	// usleep(sleep_time * 1000);
	long long	start = get_time();
	while (get_time() < start + sleep_time)
		usleep(1000);
}
// void	kill_threads(t_philo_single_data *data)
// {
// 	int	i;

// 	i = 0;
// 	pthread_mutex_destroy(&data->lp->read);
// 	pthread_mutex_destroy(&data->lp->deadlock);

// }

void	print_msg(t_philo_single_data *data, int msg, long long time)
{
	(void)time;
	pthread_mutex_lock(&data->lp->catch);
	if (dead)
	{
		pthread_mutex_unlock(&data->lp->catch);
		return ;
	}
	pthread_mutex_unlock(&data->lp->catch);
	if (msg & EAT)
	// ;
		printf("%lld philo %d is eating\n", get_time() - time, msg >> 8);
	else if (msg & SLEEP)
	// ;
		printf("%lld philo %d is sleeping\n", get_time() - time, msg >> 8);
	else if (msg & THINK)
	// ;
		printf("%lld philo %d is thinking\n", get_time() - time, msg >> 8);
	else if (msg & FORK)
	// ;
		printf("%lld philo %d has taken a fork\n", get_time() - time, msg >> 8);
}
