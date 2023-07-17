/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:47:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/17 05:01:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str && ft_isdigit(*str))
		res = (res * 10) + *(str++) - '0';
	return ((int)(res * sign));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

size_t	ft_strlen(const char *s)
{
	const char	*c;

	if (!s)
		return (0);
	c = s;
	while (*c)
		c++;
	return ((c - s));
}
