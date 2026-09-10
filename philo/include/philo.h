/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:43:34 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/10 18:29:43 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* --  LIBRARIES  -- */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <errno.h>

/* --  ERROR MESSAGES  -- */

# define TOO_MANY_ARGS	"Program must have 4 or 5 arguments"
# define NB_PHILO		"Number of philo must be an INT and bigger than 0"
# define EAT_COUNT		"Must eat count must be an INT and bigger or equal to 0"
# define TIME_VALUE		"Time argument must be a LONG and bigger than 0"
# define ERR_ALLOC 		"Cannot allocate memory"

/* --  STRUCTS  -- */

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	meals_eaten_lock;
	t_table			*table;
}	t_philo;

struct s_table
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	bool			simulation_stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

/* --  FUNCTIONS  -- */

size_t	ft_strlen(const char *s);
int		throw_error(char *err_msg, char *err_loc);
bool	parse_args(t_table *table, char **argv);
void	free_and_null(void **ptr);
void	*routine(void *arg);
bool	create_threads(t_table *table);
void	cleanup(t_table *table);
long	get_time_ms(void);

#endif