/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 03:28:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/16 03:24:14 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "../lib/libft/include/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

int	dead;			//? write
typedef struct s_philo
{
	int				philos;
	int				tm_eat;
	int				tm_sleep;
	int				tm_die;
	int				meals_number;
	long long		time;
	pthread_mutex_t	catch;
}   t_philo;

typedef struct s_philo_single_data	//?	read
{
	int				philo_id;		//?	read
	bool			eating;			//?	read
	long long		time_to_die;	//?	read
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	t_philo			*lp;
	int				eat_counter;
	int				philo_eaten_nbr_meals;
}   t_philo_single_data;

enum enum_msg
{
	EAT		= 0b1,
	SLEEP	= 0b10,
	THINK	= 0b100,
	DEAD	= 0b1000,
	FORK	= 0b10000,
};

size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_putendl_fd(char *s, int fd);
int					check_syntax(int ac, char **av);
bool				get_data(t_philo *data, int ac, char **av);
t_philo_single_data	*init_data(t_philo data);
void				take_forks(t_philo_single_data *philos, t_philo data);
void				_eat(t_philo_single_data *data);
void				_sleep(t_philo_single_data *data);
void				_think(t_philo_single_data *data);
long long			get_time();
void				sleep_job_time(long long sleep_time);
void				print_msg(t_philo_single_data *data, int msg, long long time);


#endif