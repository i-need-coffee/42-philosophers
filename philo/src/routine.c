/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 12:24:53 by shadya            #+#    #+#             */
/*   Updated: 2026/09/08 20:11:28 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	print_status(t_philo *philo, char *status);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "is eating");
	usleep(table->time_to_eat * 1000);
	print_status(philo, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	print_status(philo, "is thinking");
	return (NULL);
}

static bool	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->table->start_time;
	if (timestamp < 0)
		return (false);
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (true);
}
