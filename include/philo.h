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
}   t_philo;

typedef struct s_philo_single_data
{
	int				philo_id;
	bool			dead;
	bool			eat;
	bool			sleep;
	long int		time_to_die;
	pthread_mutex_t	mtx;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	pthread_mutex_t	lock;
	pthread_t		thread;
	t_philo			lp;
}   t_philo_single_data;

typedef enum s_msg
{
	FORK	= 0b1,
	EAT		= 0b10,
	THINK	= 0b100,
	SLEEP	= 0b1000,
	DEAD	= 0b10000
}	t_msg;

#endif