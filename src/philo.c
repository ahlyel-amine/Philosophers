/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:57:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 22:19:56 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_syntax(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!str_is_digit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{
	(void)av;

	if ((ac == 5 || ac == 6) && !check_syntax(ac, av))
		return (ft_putendl_fd("invalid arguments", 2), 0);
	if (ac == 5)
	{
		;
	}
	else if (ac == 6)
	{
		;
	}
	else
		ft_putendl_fd("invalid arguments", 2);
	return (0);
}