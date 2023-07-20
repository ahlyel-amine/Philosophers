/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:06:28 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/20 05:27:41 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

bool	get_data(t_philo *data, int ac, char **av)
{
	data->philos = ft_atoi(av[1]);
	data->tm_die = ft_atoi(av[2]);
	data->tm_eat = ft_atoi(av[3]);
	data->tm_sleep = ft_atoi(av[4]);
	if (data->philos > 200 || data->philos < 1 || data->tm_die < 60 || \
	data->tm_eat < 60 || data->tm_sleep < 60)
		return (ft_putendl_fd("philo : invalid arguments", 2), true);
	data->meals_number = -1;
	if (ac == 6)
	{
		data->meals_number = ft_atoi(av[5]);
		if (data->meals_number < 1)
			return (ft_putendl_fd("philo : invalid arguments", 2), true);
	}
	return (false);
}
