/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:57:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/16 03:04:04 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int ac, char **av)
{
	t_philo	data;

	memset(&data, 0, sizeof(data));
	if ((ac == 5 || ac == 6))
	{
		if (!check_syntax(ac, av))
			return (ft_putendl_fd("invalid arguments", 2), 0);
		if (get_data(&data, ac, av))
			return (1);
	}
	if (ac == 5 || ac == 6)
		take_forks(init_data(data), data);
	// else if (ac == 6)
	// 	;
	else
		ft_putendl_fd("invalid arguments", 2);
	return (0);
}
