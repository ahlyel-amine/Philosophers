#ifndef PHILO_H
# define PHILO_H

#include "../lib/libft/include/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
typedef struct s_philo
{
	int	philos;
	int	tm_eat;
	int	tm_sleep;
	int	tm_die;
	int	eat_counter;
	int	current_philo;
}   t_philo;

typedef struct s_philo_single_data
{
	pthread_mutex_t	mtx;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	pthread_t		thread;
	t_philo			lp;
}   t_philo_single_data;
#endif