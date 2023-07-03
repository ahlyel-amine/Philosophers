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

long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (perror("gettimeofday() FAILURE"), 0);
	return ((tv.tv_sec * (long int)1000) + (tv.tv_usec / 1000));
}

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

void	print_msg(int flag)
{
	if (flag & FORK)
		printf("PHILO %d has taken a fork\n", (flag >> 8));
	else if (flag & SLEEP)
		printf("PHILO %d is sleeping\n", (flag >> 8));
	else if (flag & THINK)
		printf("PHILO %d is thinking\n", (flag >> 8));
	else if (flag & EAT)
		printf("PHILO %d is eating\n", (flag >> 8));
	else if (flag & DEAD)
		printf("PHILO %d is dead\n", (flag >> 8));
}

void	time_sleep(int time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

void	eat(t_philo_single_data *data)
{
	pthread_mutex_lock(&data->left);
	print_msg((data->philo_id << 8 | FORK));
	pthread_mutex_lock(&data->right);
	print_msg((data->philo_id << 8 | FORK));
	pthread_mutex_lock(&data->lock);
	data->eat = true;
	print_msg((data->philo_id << 8 | EAT));
	time_sleep(data->lp.tm_eat);
	data->eat = false;
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_unlock(&data->left);
	pthread_mutex_unlock(&data->right);
	print_msg((data->philo_id << 8 | SLEEP));
	time_sleep(data->lp.tm_sleep);
}

void	sleep_(t_philo_single_data *data)
{
	struct timeval	tv;
	long int a;
	long int b;
	gettimeofday(&tv, NULL);
	b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	a = b + data->lp.tm_sleep;
	printf("%ld PHILO %d is sleeping\n",b, data->philo_id);
	while (b <= a)
	{
		gettimeofday(&tv, NULL);
		b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}
void	*catch(t_philo_single_data *data)
{
	while (!data->dead)
	{
		pthread_mutex_lock(&data->lock);
		if (get_time() >= data->time_to_die && !data->eat)
		{
			data->dead = true;
			print_msg((data->philo_id << 8) | DEAD);
		}
		pthread_mutex_unlock(&data->lock);
	}
	return (NULL);
}

void	routine(t_philo_single_data *data)
{

	data->time_to_die = get_time() + data->lp.tm_die;
	pthread_create(&data->thread, NULL, (void *)catch, data);
	// pthread_mutex_lock(&data->lock);
	while (data->dead == false)
	{
		eat(data);
		print_msg((data->philo_id << 8 | THINK));
	}
	// pthread_mutex_unlock(&data->lock);
	pthread_join(data->thread, NULL);
}

void	routine_a(t_philo_single_data *data)
{
	struct timeval	tv;
	long int b;
	long int time_die;
	gettimeofday(&tv, NULL);
	b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time_die = b + data->lp.tm_die;
	while (b < time_die)
	{
		pthread_mutex_lock(&data->left);
		pthread_mutex_lock(&data->right);
		printf("%ld PHILO %d TAKE A FORK\n",b, data->philo_id);
		eat(data);
		gettimeofday(&tv, NULL);
		b = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (b > time_die)
			exit(1);
		printf("%ld PHILO %d is thinking\n",b, data->philo_id);
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
		philos[i].lp = data;
		pthread_create(&(philos[i].thread), NULL, (void *)routine, &(philos[i]));
		time_sleep(1);
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
	t_philo_single_data	*mtx;
	int					i;

	mtx = malloc(sizeof(t_philo_single_data) * data.philos);
	i = -1;
	while (++i < data.philos)
	{
		mtx[i].philo_id = i + 1;
		mtx[i].dead = false;
		mtx[i].eat = false;
		mtx[i].sleep = false;
		pthread_mutex_init(&mtx[i].left, NULL);
		pthread_mutex_init(&mtx[i].lock, NULL);
	}
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
