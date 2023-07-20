/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 03:28:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/20 06:02:14 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				dead;
	int				philos;
	int				tm_eat;
	int				tm_sleep;
	int				tm_die;
	int				meals_number;
	int				philo_eaten_nbr_meals;
	long long		time;
	pthread_mutex_t	catch;
}	t_philo;

typedef struct s_philo_single_data
{
	int				philo_id;
	long long		time_to_die;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	t_philo			*lp;
	int				eat_counter;
	bool			eaten;
}	t_philo_single_data;

enum	e_msg
{
	EAT = 0b1,
	SLEEP = 0b10,
	THINK = 0b100,
	DEAD = 0b1000,
	FORK = 0b10000,
};

size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_putendl_fd(char *s, int fd);
int					check_syntax(int ac, char **av);
bool				get_data(t_philo *data, int ac, char **av);
void				take_forks(t_philo_single_data *philos, t_philo data);
void				_eat(t_philo_single_data *data);
void				_sleep(t_philo_single_data *data);
void				_think(t_philo_single_data *data);
long long			get_time(void);
void				sleep_job_time(long long sleep_time);
void				print_msg(t_philo_single_data *data, int msg, \
long long time);
t_philo_single_data	*init_data(t_philo_single_data *mtx, t_philo data);

#endif