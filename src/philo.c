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

void	get_data(t_philo *data, int ac, char **av)
{
	data->philos = ft_atoi(av[1]);
	data->tm_die = ft_atoi(av[2]);
	data->tm_eat = ft_atoi(av[3]);
	data->tm_sleep = ft_atoi(av[4]);
	data->eat_counter = -1;
	if (ac == 6)
		data->eat_counter = ft_atoi(av[5]);
}

void	eat(t_philo_single_data *data)
{
	struct timeval	tv;
	long int a;
	long int b;
	gettimeofday(&tv, NULL);
	b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	a = b + data->lp.tm_eat;
	// printf("%ld %ld %d\n",a,b, data->lp.tm_eat);

		printf("%ld PHILO %d is eating\n",b, data->lp.current_philo);
	while (b < a)
	{
		gettimeofday(&tv, NULL);
		b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}

void	sleep_(t_philo_single_data *data)
{
	struct timeval	tv;
	long int a;
	long int b;
	gettimeofday(&tv, NULL);
	b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	a = b + data->lp.tm_sleep;
	printf("%ld PHILO %d is sleeping\n",b, data->lp.current_philo);
	while (b <= a)
	{
		gettimeofday(&tv, NULL);
		b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}

void	routine(t_philo_single_data *data)
{
	struct timeval	tv;
	long int b;
	long int time_die;
	gettimeofday(&tv, NULL);
	b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time_die = b + data->lp.tm_die;
	while (b < time_die)
	{
		pthread_mutex_trylock(&data->left);
		pthread_mutex_trylock(&data->right);
		printf("%ld PHILO %d TAKE A FORK\n",b, data->lp.current_philo);
		eat(data);
		gettimeofday(&tv, NULL);
		b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (b > time_die)
			exit(1);
		printf("%ld PHILO %d is thinking\n",b, data->lp.current_philo);
		pthread_mutex_unlock(&data->left);
		pthread_mutex_unlock(&data->right);
		sleep_(data);
		gettimeofday(&tv, NULL);
		b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (b > time_die)
			exit(1);
		time_die = b + data->lp.tm_die;
	}
}

void	take_forks(t_philo_single_data *philos, t_philo data)
{
	int	i;

	i = 0;
	while (i < data.philos)
	{	
		(philos[i]).lp.current_philo = i + 1;
		philos[i].lp.tm_eat = data.tm_eat;
		philos[i].lp.tm_sleep = data.tm_sleep;
		philos[i].lp.tm_die = data.tm_die;
		pthread_create(&(philos[i].thread), NULL, (void *)routine, &(philos[i]));

		i++;
	}
	i = 0;
	while (i < data.philos)
	{	
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
t_philo_single_data	*init_data(t_philo data)
{
	int	i;
	t_philo_single_data *mtx;
	mtx = malloc(sizeof(t_philo_single_data) * data.philos);
	i = -1;
	while (++i < data.philos)
		pthread_mutex_init(&mtx[i].left, NULL);
	mtx[0].right = mtx[data.philos - 1].left;
	i = 0;
	while (++i < data.philos)
		mtx[i].right = mtx[i - 1].left;
	return (mtx);
}

int main(int ac, char **av)
{
	t_philo	data;

	if ((ac == 5 || ac == 6) && !check_syntax(ac, av))
		return (ft_putendl_fd("invalid arguments", 2), 0);
	get_data(&data, ac, av);
	if (ac == 5)
		take_forks(init_data(data), data);
	else if (ac == 6)
		;
	else
		ft_putendl_fd("invalid arguments", 2);
	return (0);
}
