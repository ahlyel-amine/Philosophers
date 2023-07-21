/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:57:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/21 00:50:45 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_philo				data;
	t_philo_single_data	mtx[PHILO_MAX];

	if ((ac == 5 || ac == 6))
	{
		if (!check_syntax(ac, av))
			return (ft_putendl_fd("invalid arguments", 2), 1);
		if (get_data(&data, ac, av))
			return (1);
	}
	if (ac == 5 || ac == 6)
		take_forks(init_data((t_philo_single_data *)mtx, data), data);
	else
		return (ft_putendl_fd("invalid arguments", 2), 0);
	return (0);
}
