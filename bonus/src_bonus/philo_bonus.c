/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:57:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/20 05:32:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	data;

	if ((ac == 5 || ac == 6))
	{
		if (!check_syntax(ac, av))
			return (ft_putendl_fd("invalid arguments", 2), 1);
		if (get_data(&data, ac, av))
			return (1);
	}
	if (ac == 5 || ac == 6)
		take_forks(data);
	else
		return (ft_putendl_fd("invalid arguments", 2), 0);
	return (0);
}
