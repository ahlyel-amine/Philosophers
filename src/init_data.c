/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:06:28 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/16 01:06:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_data(t_philo *data, int ac, char **av)
{
	dead = false;
	data->philos = ft_atoi(av[1]);
	data->tm_die = ft_atoi(av[2]);
	data->tm_eat = ft_atoi(av[3]);
	data->tm_sleep = ft_atoi(av[4]);
	if (data->philos > 200 || data->tm_die < 60 || \
	data->tm_eat < 60 || data->tm_sleep < 60)
		return (ft_putendl_fd("philo : invalid arguments", 2), true);
	data->meals_number = -1;
	if (ac == 6)
		data->meals_number = ft_atoi(av[5]);
	if (pthread_mutex_init(&data->catch, NULL))
		return (ft_putendl_fd("philo : init mutex faillure", 2), true);
	return (false);
}
t_philo_single_data	*init_data(t_philo data)
{
	int	i;
	t_philo_single_data *mtx;
	mtx = malloc(sizeof(t_philo_single_data) * data.philos);
	if (!mtx)
		return (NULL);
	i = -1;
	while (++i < data.philos)
		if (pthread_mutex_init(&mtx[i].left, NULL))
			return (free(mtx), /*mutexes_destroy_at(i, data), */\
			ft_putendl_fd("philo : init mutex faillure", 2), NULL);
	mtx[0].right = &mtx[data.philos - 1].left;
	i = 0;
	while (++i < data.philos)
		mtx[i].right = &mtx[i - 1].left;
	return (mtx);
}
