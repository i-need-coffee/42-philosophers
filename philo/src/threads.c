/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 07:51:54 by shadya            #+#    #+#             */
/*   Updated: 2026/09/05 19:51:51 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *data);
static long	get_time_in_ms(void);

bool	create_and_join_threads(t_table *table)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, &routine, table) != 0)
		return (throw_error(strerror(errno), "pthread_create"), false);
	if (pthread_join(philo, NULL) != 0)
		return (throw_error(strerror(errno), "pthread_join"), false);
	return (true);
}

static void	*routine(void *data)
{
	t_table	*table;
	long	start;

	table = (t_table *)data;
	start = get_time_in_ms();
	while (1)
	{
		printf("%ld 1 has taken a fork\n", (get_time_in_ms() - start));
		printf("%ld 1 is eating\n", (get_time_in_ms() - start));
		usleep(table->time_to_eat * 1000);
		printf("%ld 1 is sleeping\n", (get_time_in_ms() - start));
		usleep(table->time_to_sleep * 1000);
		printf("%ld 1 is thinking\n", (get_time_in_ms() - start));
	}
	return (NULL);
}

static long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			seconds;
	long			microseconds;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec;
	microseconds = tv.tv_usec;
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (milliseconds);
}
