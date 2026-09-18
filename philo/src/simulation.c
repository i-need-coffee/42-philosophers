/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:25:44 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/18 14:39:18 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_stopped(t_table *table)
{
	bool	has_stopped;

	pthread_mutex_lock(&table->stop_lock);
	has_stopped = table->simulation_stop;
	pthread_mutex_unlock(&table->stop_lock);
	return (has_stopped);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_lock);
	table->simulation_stop = true;
	pthread_mutex_unlock(&table->stop_lock);
}

bool	wait_for_start(t_table *table)
{
	bool	ready;
	bool	stopped;

	while (true)
	{
		pthread_mutex_lock(&table->stop_lock);
		ready = table->ready;
		stopped = table->simulation_stop;
		pthread_mutex_unlock(&table->stop_lock);
		if (stopped)
			return (false);
		if (ready)
			return (true);
		usleep(100);
	}
}

bool	start_simulation(t_table *table)
{
	long	now;
	int		i;

	now = get_time_ms();
	if (now < 0)
	{
		stop_simulation(table);
		return (false);
	}
	pthread_mutex_lock(&table->stop_lock);
	table->start_time = now;
	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].last_meal = now;
		i++;
	}
	table->ready = true;
	pthread_mutex_unlock(&table->stop_lock);
	return (true);
}
