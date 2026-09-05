/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:43:34 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/05 19:49:01 by shadya           ###   ########.fr       */
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

typedef struct s_table
{
	int		nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		must_eat_count;
}	t_table;

/* --  FUNCTIONS  -- */

size_t	ft_strlen(const char *s);
int		throw_error(char *err_msg, char *err_loc);
bool	parse_args(t_table *table, char **argv);
bool	create_and_join_threads(t_table *table);
void	free_and_null(void **ptr);

#endif