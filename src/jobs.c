/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:11:13 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/15 09:30:18 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	_sleep(t_philo_single_data *data)
{
	print_msg(data, (data->philo_id << 8) | SLEEP, data->lp->time);
	sleep_job_time(data->lp->tm_sleep);
}

void	_think(t_philo_single_data *data)
{
	print_msg(data, (data->philo_id << 8) | THINK, data->lp->time);
}