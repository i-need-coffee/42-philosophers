/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 12:24:53 by shadya            #+#    #+#             */
/*   Updated: 2026/09/06 15:04:19 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(long ms);
static long	get_time_ms(void);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	long	start;

	philo = (t_philo *)arg;
	table = philo->table;
	start = get_time_ms();
	printf("%ld %d has taken a fork\n", (get_time_ms() - start), philo->id);
	printf("%ld %d is eating\n", (get_time_ms() - start), philo->id);
	ft_usleep(table->time_to_eat);
	printf("%ld %d is sleeping\n", (get_time_ms() - start), philo->id);
	ft_usleep(table->time_to_sleep);
	printf("%ld %d is thinking\n", (get_time_ms() - start), philo->id);
	return (NULL);
}

static void	ft_usleep(long ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(500);
}

static long	get_time_ms(void)
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
